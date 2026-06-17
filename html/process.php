<?php
declare(strict_types=1);

const SUBMISSIONS_FILE = __DIR__ . '/order_submissions.jsonl';

function respond(int $statusCode, string $title, string $message, array $orders = []): void
{
    http_response_code($statusCode);
    header('Content-Type: text/html; charset=UTF-8');

    $safeTitle = htmlspecialchars($title, ENT_QUOTES, 'UTF-8');
    $safeMessage = htmlspecialchars($message, ENT_QUOTES, 'UTF-8');
    $backUrl = isset($_SERVER['HTTP_REFERER']) ? basename((string) $_SERVER['HTTP_REFERER']) : 'ktra.html';

    if (!preg_match('/^[A-Za-z0-9_.-]+\.html$/', $backUrl)) {
        $backUrl = 'ktra.html';
    }

    echo '<!DOCTYPE html><html lang="en"><head><meta charset="UTF-8">';
    echo '<meta name="viewport" content="width=device-width, initial-scale=1.0">';
    echo "<title>{$safeTitle}</title>";
    echo '<style>body{font-family:Arial,sans-serif;max-width:720px;margin:40px auto;padding:0 20px;line-height:1.5}';
    echo 'table{border-collapse:collapse;width:100%;margin:20px 0}th,td{border:1px solid #ccc;padding:8px;text-align:left}';
    echo '.status{padding:16px;border-radius:6px;background:#eef8f7;border:1px solid #57a8a6}.error{background:#fff0f0;border-color:#cc4444}';
    echo 'a{display:inline-block;margin-top:12px;color:#0b6b68}</style></head><body>';
    echo '<div class="status' . ($statusCode >= 400 ? ' error' : '') . '">';
    echo "<h1>{$safeTitle}</h1><p>{$safeMessage}</p></div>";

    if ($orders) {
        echo '<table><thead><tr><th>Order No</th><th>Saved Value</th></tr></thead><tbody>';
        foreach ($orders as $order) {
            $id = htmlspecialchars((string) $order['id'], ENT_QUOTES, 'UTF-8');
            $value = htmlspecialchars((string) $order['value'], ENT_QUOTES, 'UTF-8');
            echo "<tr><td>{$id}</td><td>{$value}</td></tr>";
        }
        echo '</tbody></table>';
    }

    $safeBackUrl = htmlspecialchars($backUrl, ENT_QUOTES, 'UTF-8');
    echo "<a href=\"{$safeBackUrl}\">Back to orders</a>";
    echo '</body></html>';
}

function getSelectedOrderIds(): array
{
    $rawIds = $_POST['orders'] ?? $_POST['order_ids'] ?? [];

    if (!is_array($rawIds)) {
        return [];
    }

    $ids = [];
    foreach ($rawIds as $rawId) {
        $id = trim((string) $rawId);
        if ($id !== '' && preg_match('/^[A-Za-z0-9 _-]{1,32}$/', $id)) {
            $ids[] = $id;
        }
    }

    return array_values(array_unique($ids));
}

function getOrderValues(): array
{
    $rawValues = $_POST['values'] ?? [];

    if (!is_array($rawValues)) {
        return [];
    }

    $values = [];
    foreach ($rawValues as $orderId => $rawValue) {
        $id = trim((string) $orderId);
        $cleanValue = preg_replace('/[^\d.-]/', '', (string) $rawValue);

        if ($id === '' || $cleanValue === '' || !preg_match('/^[A-Za-z0-9 _-]{1,32}$/', $id)) {
            continue;
        }

        $value = (float) $cleanValue;
        if (is_finite($value)) {
            $values[$id] = $value;
        }
    }

    return $values;
}

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    respond(405, 'Method not allowed', 'Use the Save button from the orders page to submit changes.');
    exit;
}

$selectedIds = getSelectedOrderIds();
$valuesById = getOrderValues();

if (!$selectedIds) {
    respond(400, 'No orders selected', 'Select at least one order before saving.');
    exit;
}

$orders = [];
foreach ($selectedIds as $id) {
    if (!array_key_exists($id, $valuesById)) {
        respond(400, 'Missing order value', "No value was submitted for order {$id}.");
        exit;
    }

    $orders[] = [
        'id' => $id,
        'value' => $valuesById[$id],
    ];
}

$submission = [
    'submitted_at' => gmdate('c'),
    'source' => isset($_SERVER['HTTP_REFERER']) ? basename((string) $_SERVER['HTTP_REFERER']) : null,
    'orders' => $orders,
];

$encoded = json_encode($submission, JSON_UNESCAPED_SLASHES);

if ($encoded === false || file_put_contents(SUBMISSIONS_FILE, $encoded . PHP_EOL, FILE_APPEND | LOCK_EX) === false) {
    respond(500, 'Save failed', 'The server could not save the selected orders. Please try again.');
    exit;
}

respond(200, 'Orders saved', 'Your selected order values were saved successfully.', $orders);
