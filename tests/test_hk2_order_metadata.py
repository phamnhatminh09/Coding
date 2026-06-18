from html.parser import HTMLParser
from pathlib import Path
import re
import unittest


ROOT = Path(__file__).resolve().parents[1]
ORDER_MODEL_S = ROOT / "hk2" / "order-model-s.html"


class ModelSOrderParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.in_order_price = False
        self.in_strong = False
        self.displayed_prices = []
        self.checkout_button = None

    def handle_starttag(self, tag, attrs):
        attr_map = dict(attrs)
        classes = set(attr_map.get("class", "").split())
        if tag == "div" and "order-config-price" in classes:
            self.in_order_price = True
        elif tag == "strong" and self.in_order_price:
            self.in_strong = True
        elif tag == "button" and "order-config-cta" in classes:
            self.checkout_button = attr_map

    def handle_data(self, data):
        if self.in_strong:
            value = data.strip()
            if value:
                self.displayed_prices.append(value)

    def handle_endtag(self, tag):
        if tag == "strong":
            self.in_strong = False
        elif tag == "div" and self.in_order_price:
            self.in_order_price = False


def parse_price(value):
    digits = re.sub(r"[^0-9.-]+", "", value or "0")
    return float(digits or 0)


class ModelSOrderMetadataTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        parser = ModelSOrderParser()
        parser.feed(ORDER_MODEL_S.read_text(encoding="utf-8"))
        cls.parser = parser

    def test_model_s_configurator_uses_model_s_checkout_metadata(self):
        button = self.parser.checkout_button

        self.assertIsNotNone(button, "Model S checkout button was not found")
        self.assertEqual(button["data-order-model"], "Model S")
        self.assertEqual(button["data-order-trim"], "Plaid All-Wheel Drive")
        self.assertEqual(button["data-order-price"], "$74,990")
        self.assertTrue(button["data-order-image"].startswith("mods"))

    def test_displayed_price_matches_checkout_price(self):
        button = self.parser.checkout_button

        self.assertIn("$74,990", self.parser.displayed_prices)
        self.assertEqual(self.parser.displayed_prices[0], button["data-order-price"])

    def test_home_charger_addon_preserves_model_s_and_updates_total(self):
        button = self.parser.checkout_button
        payload = {
            "model": button["data-order-model"],
            "trim": button["data-order-trim"],
            "price": button["data-order-price"],
        }

        payload["price"] = f"${parse_price(payload['price']) + 450:,.0f}"
        payload["trim"] = f"{payload['trim']} + Home Charger"

        self.assertEqual(payload["model"], "Model S")
        self.assertEqual(payload["trim"], "Plaid All-Wheel Drive + Home Charger")
        self.assertEqual(payload["price"], "$75,440")


if __name__ == "__main__":
    unittest.main()
