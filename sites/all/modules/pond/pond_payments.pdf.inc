<?php

//pond_payments_pdf_generate

function pond_payments_pdf_display($payment_id) {
  //Todo: Access Checking.
  $vars = array();

  $payment = entity_load_single('payment', $payment_id);
  if(empty($payment)){
    dpm('Payment '.$payment_id.' Not Found');
    return MENU_NOT_FOUND;
  }
  $account = user_load($payment->uid);
  if(empty($account->uid)){
    return MENU_NOT_FOUND;
  }

  $vars['payment_id'] = $payment->pid;
  
  $currency = currency_load($payment->currency_code);
  $vars['currency'] = $payment->currency_code;
  $vars['currency_symbol'] = $currency->sign;

  $vars['amount'] = $payment->totalAmount(1);
  foreach($payment->statuses as $status){
    if($status->status == 'payment_status_success'){
      $vars['payment_date'] = date('d M Y', $status->created);
    }
  }

  if(empty($vars['payment_date'])){//This payment did not complete successfully, throw error.
    dpm('Payment was not successful.');
    return MENU_NOT_FOUND;
  }

  $info = pond_get_by_uid($payment->uid);
  $vars['name'] = $info['full_name'];
  $vars['address'] = $info['formatted_address'];
  $vars['amount_owing'] = $info['finances']['owing'];

  /*dpm($payment);
  dpm($info);
  dpm($vars);
  return 'Hello';*/

  $pdf = pond_payments_pdf_generate($vars);


  if (!$pdf) {
    return t('An error occured.');
  }

  // Tell the browser that this is not an HTML file to show, but a pdf file to
  // download.
  header('Content-Type: application/pdf');
  header('Content-Length: ' . strlen($pdf));
  header('Content-Disposition: attachment; filename="PondReceipt.pdf"');
  print $pdf;
  return NULL;
}




/**
 * Generates a pdf file using TCPDF module.
 *
 * @return string Binary string of the generated pdf.
 */
function pond_payments_pdf_generate($variables) {


  // Get the content we want to convert into pdf.
  $html = theme('pond_payments_pdf_content', $variables);

  $tcpdf = tcpdf_get_instance();

  $tcpdf->DrupalInitialize(array(
    'footer' => array(
      'callback' => 'pond_payments_pdf_generate_footer',
    ),
    'header' => array(
      'callback' => 'pond_payments_pdf_generate_header',
    ),
  ));
  $tcpdf->SetFooterMargin(30);
  $tcpdf->SetTopMargin(50);
  // Insert the content. Note that DrupalInitialize automaticly adds the first
  // page to the pdf document.
  $tcpdf->writeHTML($html);

  return $tcpdf->Output('', 'S');
}


/**
 * Callback for generating the header. This function acts like if it overridded
 *   the Header() function of tcpdf class except the tcpdf instance is not $this
 *   but a parameter.
 *
 * @param type $tcpdf TCPDFDrupal instance. It can be used as $this in the
 *   Header() function of a siebling of TCPDF.
 */
function pond_payments_pdf_generate_header(&$tcpdf) {
  $header_image_path = path_to_theme().'/images/pdf_receipt_top.gif';//Todo: Make this a setting.
  $tcpdf->Image(drupal_realpath($header_image_path), 0, 0, 210);
}
function pond_payments_pdf_generate_footer(&$tcpdf) {
  $header_image_path = path_to_theme().'/images/pdf_receipt_bottom.gif';//Todo: Make this a setting.
  $tcpdf->Image(drupal_realpath($header_image_path), 0, '', 210);
}
