#include "Seeed_erpcUnified.h"

T_APP_RESULT ble_gap_callback(uint8_t cb_type, void *p_cb_data)
{
  T_APP_RESULT result = APP_RESULT_SUCCESS;
  T_LE_CB_DATA *p_data = (T_LE_CB_DATA *)p_cb_data;
  switch (cb_type)
  {
  case GAP_MSG_LE_SCAN_INFO:
  {
    Serial.printf("GAP_MSG_LE_SCAN_INFO:adv_type 0x%x\n\r", p_data->p_le_scan_info->adv_type);
    Serial.printf("bd_addr %02x:%02x:%02x:%02x:%02x:%02x\n\r",
                  (p_data->p_le_scan_info->bd_addr)[5],
                  (p_data->p_le_scan_info->bd_addr)[4],
                  (p_data->p_le_scan_info->bd_addr)[3],
                  (p_data->p_le_scan_info->bd_addr)[2],
                  (p_data->p_le_scan_info->bd_addr)[1],
                  (p_data->p_le_scan_info->bd_addr)[0]);
    Serial.printf("remote_addr_type %d, rssi %d, data_len %d\n\r",
                  p_data->p_le_scan_info->remote_addr_type,
                  p_data->p_le_scan_info->rssi,
                  p_data->p_le_scan_info->data_len);
  }
  break;
  }
  return result;
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial)
  {
  };

  Serial.printf("rpc_ble_init\n\r");
  rpc_ble_init();
  Serial.printf("rpc_gap_config_max_le_link_num\n\r");
  rpc_gap_config_max_le_link_num(3);
  Serial.printf("rpc_le_gap_init\n\r");
  rpc_le_gap_init(3);
  Serial.printf("rpc_ble_start\n\r");
  le_register_app_cb(ble_gap_callback);
  rpc_ble_start();

  rpc_le_scan_start();
  delay(10000);
  rpc_le_scan_stop();
}

void loop()
{
  // rpc_le_scan_start();
  // delay(10000);
  // rpc_le_scan_stop();
  // delay(5000);
}
