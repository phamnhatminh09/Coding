from html.parser import HTMLParser
from pathlib import Path
import unittest


ORDER_PAGES = sorted((Path(__file__).resolve().parents[1] / "hk2").glob("order-*.html"))


class OrderPageParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.heading = None
        self.displayed_price = None
        self.order_payload = None
        self._capture = None
        self._in_order_price = False
        self._order_price_depth = 0

    def handle_starttag(self, tag, attrs):
        attrs_dict = dict(attrs)
        class_names = attrs_dict.get("class", "").split()

        if "order-config-price" in class_names:
            self._in_order_price = True
            self._order_price_depth = 1
        elif self._in_order_price:
            self._order_price_depth += 1

        if tag == "h1" and self.heading is None:
            self._capture = "heading"
        elif tag == "strong" and self._in_order_price and self.displayed_price is None:
            self._capture = "price"
        elif tag == "button" and "data-order-model" in attrs_dict:
            self.order_payload = attrs_dict

    def handle_endtag(self, tag):
        if self._capture and tag in {"h1", "strong"}:
            self._capture = None

        if self._in_order_price:
            self._order_price_depth -= 1
            if self._order_price_depth == 0:
                self._in_order_price = False

    def handle_data(self, data):
        value = data.strip()
        if not value:
            return

        if self._capture == "heading" and self.heading is None:
            self.heading = value
        elif self._capture == "price" and self.displayed_price is None:
            self.displayed_price = value


class OrderPayloadTests(unittest.TestCase):
    def test_checkout_payload_matches_visible_order_details(self):
        self.assertTrue(ORDER_PAGES, "expected hk2 order pages to exist")

        for page in ORDER_PAGES:
            with self.subTest(page=page.name):
                parser = OrderPageParser()
                parser.feed(page.read_text(encoding="utf-8"))

                self.assertIsNotNone(parser.order_payload)
                self.assertEqual(parser.heading, parser.order_payload.get("data-order-model"))
                self.assertEqual(parser.displayed_price, parser.order_payload.get("data-order-price"))
                self.assertTrue(parser.order_payload.get("data-order-image"))


if __name__ == "__main__":
    unittest.main()
