<html>
  <body id="pdf-receipt">
    <table id="positioning-table"><tr>
      <td>
        <h1 id="receipt-number" style="margin-bottom: 0;">Receipt No. <?php print $payment_id; ?></h1>
        <p><?php print $payment_date; ?></p>
        <p><?php print $name; ?> <br />
          <?php print $address; ?></p>
        <p id="amount-paid" style="font-weight:bold; font-size: 2em;">Amount Paid: <?php print $currency . ' ' . $currency_symbol . number_format($amount, 2); ?></p>
        <p id="amount-owing" style="color:red;font-weight: bold;">Amount Outstanding: <?php print $currency . ' ' . $currency_symbol . number_format($amount_owing, 2); ?></p>
      </td>
      <td>
        <p id="address">322 Wrecker Rd, Mansfield QLD 4122<br />
          T: 07 3343 8888<br />
          F: 07 3343 9291<br />
          E: finance@redfrogs.com.au<br />
          ABN: 42 154 689 353
        </p>
      </td>
    </tr></table>
  </body>
</html>