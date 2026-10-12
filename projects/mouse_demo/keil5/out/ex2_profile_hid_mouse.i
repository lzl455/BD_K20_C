# 1 "../main/ex2_profile_hid_mouse.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 350 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "../main/ex2_profile_hid_mouse.c" 2
# 13 "../main/ex2_profile_hid_mouse.c"
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 1 3
# 56 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 3
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int int64_t;


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;





typedef signed char int_least8_t;
typedef signed short int int_least16_t;
typedef signed int int_least32_t;
typedef signed long long int int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long int uint_least64_t;




typedef signed int int_fast8_t;
typedef signed int int_fast16_t;
typedef signed int int_fast32_t;
typedef signed long long int int_fast64_t;


typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long int uint_fast64_t;






typedef signed int intptr_t;
typedef unsigned int uintptr_t;



typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
# 14 "../main/ex2_profile_hid_mouse.c" 2
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdbool.h" 1 3
# 15 "../main/ex2_profile_hid_mouse.c" 2
# 1 "../../../components/exble2/includes\\ex2_api.h" 1
# 18 "../../../components/exble2/includes\\ex2_api.h"
# 1 "../../../components/exble2/includes/core_ble.h" 1
# 16 "../../../components/exble2/includes/core_ble.h"
# 1 "../../../components/exble2/includes/ble/exe_hal_tc.h" 1
# 17 "../../../components/exble2/includes/core_ble.h" 2

# 1 "../../../components/exble2/includes/ble/ble_ll.h" 1
# 29 "../../../components/exble2/includes/ble/ble_ll.h"
typedef enum {
    ADV_IND = 0x0,
    ADV_DIRECT_IND = 0x1,
    ADV_NONCONN_IND = 0x2,
    SCAN_REQ = 0x3,
    AUX_SCAN_REQ = 0x3,
    SCAN_RSP = 0x4,
    CONNECT_IND = 0x5,
    AUX_CONNECT_REQ = 0x5,
    ADV_SCAN_IND = 0x6,
    ADV_EXT_IND = 0x7,
    AUX_ADV_IND = 0x7,
    AUX_SCAN_RSP = 0x7,
    AUX_SYNC_IND = 0x7,
    AUX_CHAIN_IND = 0x7,
    AUX_CONNECT_RSP = 0x8,
} ll_adv_pdu_type_t;


typedef enum {
    LLCP_CONNECTION_UPDATE_IND,
    LLCP_CHANNEL_MAP_IND,
    LLCP_TERMINATE_IND,
    LLCP_ENC_REQ,
    LLCP_ENC_RSP,
    LLCP_START_ENC_REQ,
    LLCP_START_ENC_RSP,
    LLCP_UNKNOWN_RSP,
    LLCP_FEATURE_REQ,
    LLCP_FEATURE_RSP,
    LLCP_PAUSE_ENC_REQ,
    LLCP_PAUSE_ENC_RSP,
    LLCP_VERSION_IND,
    LLCP_REJECT_IND,
    LLCP_SLAVE_FEATURE_REQ,
    LLCP_CONNECTION_PARAM_REQ,
    LLCP_CONNECTION_PARAM_RSP,
    LLCP_REJECT_EXT_IND,
    LLCP_PING_REQ,
    LLCP_PING_RSP,

    LLCP_LENGTH_REQ,
    LLCP_LENGTH_RSP,
    LLCP_PHY_REQ,
    LLCP_PHY_RSP,
    LLCP_PHY_UPDATE_IND,
    LLCP_MIN_USED_CHANNELS_IND,

    LLCP_CTE_REQ,
    LLCP_CTE_RSP,
    LLCP_PERIODIC_SYNC_IND,
    LLCP_CLOCK_ACCURACY_REQ,
    LLCP_CLOCK_ACCURACY_RSP,
} ll_control_pdu_opcode_t;


struct __attribute__((packed, aligned(1))) _ble_adv_header_t {

    uint8_t Type :4;
    uint8_t RFU :1;
    uint8_t ChSel :1;
    uint8_t TxAdd :1;
    uint8_t RxAdd :1;

    uint8_t Length;
};
typedef struct _ble_adv_header_t ble_adv_header_t;


struct __attribute__((packed, aligned(1))) _ble_data_header_t {

    uint8_t llid :2;

    uint8_t nesn :1;

    uint8_t sn :1;

    uint8_t md :1;

    uint8_t cp :1;
    uint8_t RFU :2;

    uint8_t Length;


};

typedef union __attribute__((packed, aligned(1))) {
    struct __attribute__((packed, aligned(1))) {

        uint8_t llid :2;

        uint8_t nesn :1;

        uint8_t sn :1;

        uint8_t md :1;

        uint8_t cp :1;
        uint8_t RFU :2;

        uint8_t Length;


    };
    uint16_t all;
} ble_data_header_t;



struct __attribute__((packed, aligned(1))) _ble_adv_ind_t {
    uint8_t AdvA[6];
    uint8_t AdvData[31];
};
typedef struct _ble_adv_ind_t ble_adv_ind_t;


struct __attribute__((packed, aligned(1))) _ble_adv_direct_ind_t {
    uint8_t AdvA[6];
    uint8_t TargetA[6];
};
typedef struct _ble_adv_direct_ind_t ble_adv_direct_ind_t;


struct __attribute__((packed, aligned(1))) _ble_adv_nonconn_ind_t {
    uint8_t AdvA[6];
    uint8_t AdvData[31];
};
typedef struct _ble_adv_nonconn_ind_t ble_adv_nonconn_ind_t;


struct __attribute__((packed, aligned(1))) _ble_adv_scan_ind_t {
    uint8_t AdvA[6];
    uint8_t AdvData[31];
};
typedef struct _ble_adv_scan_ind_t ble_adv_scan_ind_t;


struct __attribute__((packed, aligned(1))) _ble_adv_scan_req_t {
    uint8_t ScanA[6];
    uint8_t AdvA[6];
};
typedef struct _ble_adv_scan_req_t ble_adv_scan_req_t;


struct __attribute__((packed, aligned(1))) _ble_adv_scan_rsp_t {
    uint8_t AdvA[6];
    uint8_t ScanRspData[31];
};
typedef struct _ble_adv_scan_rsp_t ble_adv_scan_rsp_t;


struct __attribute__((packed, aligned(1))) _ble_adv_connect_ind_t {
    uint8_t InitA[6];
    uint8_t AdvA[6];
    uint32_t AA;
    uint8_t CRCInit[3];
    uint8_t WinSize;
    uint16_t WinOffset;
    uint16_t Interval;
    uint16_t Latency;
    uint16_t Timeout;
    uint8_t ChM[5];
    uint8_t Hop :5;
    uint8_t SCA :3;
};
typedef struct _ble_adv_connect_ind_t ble_adv_connect_ind_t;


struct __attribute__((packed, aligned(1))) _ble_adv_pkt_t {
    ble_adv_header_t header;
    union __attribute__((packed, aligned(1))) {
        ble_adv_ind_t adv_ind;
        ble_adv_direct_ind_t direct_ind;
        ble_adv_nonconn_ind_t nonconn_ind;
        ble_adv_scan_ind_t scan_ind;

        ble_adv_scan_req_t scan_req;

        ble_adv_scan_rsp_t scan_rsp;

        ble_adv_connect_ind_t connect_ind;
    } payload;
};
typedef struct _ble_adv_pkt_t ble_adv_pkt_t;


struct __attribute__((packed, aligned(1))) _ble_ll_connection_update_ind_t {
    uint8_t WinSize;
    uint16_t WinOffset;
    uint16_t Interval;
    uint16_t Latency;
    uint16_t Timeout;
    uint16_t Instant;
};
typedef struct _ble_ll_connection_update_ind_t ble_ll_connection_update_ind_t;

struct __attribute__((packed, aligned(1))) _ble_ll_channel_map_ind_t {
    uint8_t ChM[5];
    uint16_t Instant;
};
typedef struct _ble_ll_channel_map_ind_t ble_ll_channel_map_ind_t;

struct __attribute__((packed, aligned(1))) _ble_ll_terminate_ind_t {
    uint8_t ErrorCode;
};
typedef struct _ble_ll_terminate_ind_t ble_ll_terminate_ind_t;

struct __attribute__((packed, aligned(1))) _ble_ll_enc_req_t {
    uint8_t Rand[8];
    uint16_t EDIV;
    uint8_t SKDm[8];
    uint8_t IVm[4];
};
typedef struct _ble_ll_enc_req_t ble_ll_enc_req_t;

struct __attribute__((packed, aligned(1))) _ble_ll_enc_rsp_t {
    uint8_t SKDs[8];
    uint8_t IVs[4];
};
typedef struct _ble_ll_enc_rsp_t ble_ll_enc_rsp_t;

struct __attribute__((packed, aligned(1))) _ble_ll_feature_req_t {
    uint8_t FeatureSet[8];
};
typedef struct _ble_ll_feature_req_t ble_ll_feature_req_t;

struct __attribute__((packed, aligned(1))) _ble_ll_feature_rsp_t {
    uint8_t FeatureSet[8];
};
typedef struct _ble_ll_feature_rsp_t ble_ll_feature_rsp_t;

struct __attribute__((packed, aligned(1))) _ble_ll_version_ind_t {
    uint8_t VersNr;
    uint16_t CompId;
    uint16_t SubVersNr;
};
typedef struct _ble_ll_version_ind_t ble_ll_version_ind_t;


struct __attribute__((packed, aligned(1))) _ble_llcp_pdu_t {
    uint8_t Opcode;
    union __attribute__((packed, aligned(1))) {

        ble_ll_connection_update_ind_t connection_update_ind;
        ble_ll_channel_map_ind_t channel_map_ind;
        ble_ll_terminate_ind_t terminate_ind;
        ble_ll_enc_req_t enc_req;
        ble_ll_enc_rsp_t enc_rsp;
        ble_ll_feature_req_t feature_req;
        ble_ll_feature_rsp_t feature_rsp;
        ble_ll_version_ind_t version_ind;
    } payload;
};
typedef struct _ble_llcp_pdu_t ble_llcp_pdu_t;


struct __attribute__((packed, aligned(1))) _ble_ll_scan_param {
    uint16_t scan_itvl;
    uint16_t scan_window;
    uint8_t filter_policy;
    uint8_t scan_type;
    uint8_t own_addr_type;
};
typedef struct _ble_ll_scan_param ble_scan_param_t;


struct __attribute__((packed, aligned(1))) _ble_ll_conn_param
{
    uint16_t scan_itvl;
    uint16_t scan_window;
    uint8_t filter_policy;
    uint8_t peer_addr_type;
    uint8_t peer_addr[6];
    uint16_t conn_itvl_min;
    uint16_t conn_itvl_max;
    uint16_t conn_latency;
    uint16_t supervision_timeout;
    uint16_t min_ce_len;
    uint16_t max_ce_len;
    uint8_t own_addr_type;
};
typedef struct _ble_ll_conn_param ble_conn_param_t;
# 19 "../../../components/exble2/includes/core_ble.h" 2
# 1 "../../../components/exble2/includes/ble/ble_l2cap.h" 1
# 24 "../../../components/exble2/includes/ble/ble_l2cap.h"
typedef enum {
    L2CAP_SIG_Command_reject = 0x01,
    L2CAP_SIG_Connection_request = 0x02,
    L2CAP_SIG_Connection_response = 0x03,
    L2CAP_SIG_Disconnection_request = 0x06,
    L2CAP_SIG_Disconnection_response = 0x07,
    L2CAP_SIG_Information_request = 0x0A,
    L2CAP_SIG_Connection_Parameter_Update_request = 0x12,
    L2CAP_SIG_Connection_Parameter_Update_response = 0x13,
    L2CAP_SIG_LE_Credit_Based_Connection_request = 0x14,
    L2CAP_SIG_LE_Credit_Based_Connection_response = 0x15,
    L2CAP_SIG_LE_Flow_Control_Credit = 0x16,
} ble_l2cap_signaling_code_t;

struct __attribute__((packed, aligned(1))) _ble_l2cap_header_t {

    uint16_t Length;

    uint16_t ChannelId;
};
typedef struct _ble_l2cap_header_t ble_l2cap_header_t;


struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_command_reject_t {



    uint16_t Reason;
};
typedef struct _ble_l2cap_signaling_command_reject_t ble_l2cap_signaling_command_reject_t;


struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_connection_request_t {

    uint16_t PSM;

    uint16_t SourceCID;
};
typedef struct _ble_l2cap_signaling_connection_request_t ble_l2cap_signaling_connection_request_t;


struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_connection_response_t {

    uint16_t DestinationCID;

    uint16_t SourceCID;

    uint16_t Result;

    uint16_t Status;
};
typedef struct _ble_l2cap_signaling_connection_response_t ble_l2cap_signaling_connection_response_t;


struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_disconnection_request_t {

    uint16_t DestinationCID;

    uint16_t SourceCID;
};
typedef struct _ble_l2cap_signaling_disconnection_request_t ble_l2cap_signaling_disconnection_request_t;


struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_disconnection_response_t {

    uint16_t DestinationCID;

    uint16_t SourceCID;
};
typedef struct _ble_l2cap_signaling_disconnection_response_t ble_l2cap_signaling_disconnection_response_t;


struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_information_request_t {


    uint16_t InfoType;
};
typedef struct _ble_l2cap_signaling_information_request_t ble_l2cap_signaling_information_request_t;


struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_connection_parameters_update_request_t {

    uint16_t IntervalMin;

    uint16_t IntervalMax;

    uint16_t SlaveLatency;

    uint16_t TimeoutMultiplier;
};
typedef struct _ble_l2cap_signaling_connection_parameters_update_request_t ble_l2cap_signaling_connection_parameters_update_request_t;


struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_connection_parameters_update_response_t {

    uint16_t Result;
};
typedef struct _ble_l2cap_signaling_connection_parameters_update_response_t ble_l2cap_signaling_connection_parameters_update_response_t;


struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_le_connection_request_t {

    uint16_t LE_PSM;

    uint16_t SourceCID;

    uint16_t MTU;

    uint16_t MPS;

    uint16_t InitialCredits;
};
typedef struct _ble_l2cap_signaling_le_connection_request_t ble_l2cap_signaling_le_connection_request_t;


struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_le_connection_response_t {

    uint16_t DestinationCID;

    uint16_t MTU;

    uint16_t MPS;

    uint16_t InitialCredits;

    uint16_t Result;
};
typedef struct _ble_l2cap_signaling_le_connection_response_t ble_l2cap_signaling_le_connection_response_t;


struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_pdu_t {

    uint8_t Code;

    uint8_t Identifier;

    uint16_t Length;
    union __attribute__((packed, aligned(1))) {

        ble_l2cap_signaling_command_reject_t cmd_rej;
        ble_l2cap_signaling_connection_request_t conn_req;
        ble_l2cap_signaling_connection_response_t conn_rsp;
        ble_l2cap_signaling_disconnection_request_t disconn_req;
        ble_l2cap_signaling_disconnection_response_t disconn_rsp;
        ble_l2cap_signaling_information_request_t info_req;
        ble_l2cap_signaling_connection_parameters_update_request_t conn_update_req;
        ble_l2cap_signaling_connection_parameters_update_response_t conn_update_rsp;
        ble_l2cap_signaling_le_connection_request_t le_conn_req;
        ble_l2cap_signaling_le_connection_response_t le_conn_rsp;
    } payload;
};
typedef struct _ble_l2cap_signaling_pdu_t ble_l2cap_signaling_pdu_t;

struct __attribute__((packed, aligned(1))) _ble_l2cap_signaling_pkt_t {
    ble_data_header_t header;
    ble_l2cap_header_t l2cap;
    ble_l2cap_signaling_pdu_t signal;
};
typedef struct _ble_l2cap_signaling_pkt_t ble_l2cap_signaling_pkt_t;
# 20 "../../../components/exble2/includes/core_ble.h" 2
# 1 "../../../components/exble2/includes/ble/ble_smp.h" 1
# 17 "../../../components/exble2/includes/ble/ble_smp.h"
typedef enum {
    SMP_Pairing_Request = 0x01,
    SMP_Pairing_Response,
    SMP_Pairing_Confirm,
    SMP_Pairing_Random,
    SMP_Pairing_Failed,
    SMP_Encryption_Information,
    SMP_Master_Identification,
    SMP_Identity_Information,
    SMP_Identity_Address_Information,
    SMP_Signing_Information,
    SMP_Security_Request,

    SMP_Pairing_Public_Key,
    SMP_Pairing_DHKey_Check,
    SMP_Pairing_Keypress_Notification,
} smp_command_codes_t;


struct __attribute__((packed, aligned(1))) _ble_key_distribution_t {
    uint8_t EncKey :1;
    uint8_t IdKey :1;
    uint8_t SignKey :1;
    uint8_t LinkKey :1;
    uint8_t RFU :4;
};
typedef struct _ble_key_distribution_t ble_key_distribution_t;



struct __attribute__((packed, aligned(1))) _ble_smp_pairing_request_response_t {
    uint8_t IOCapability;
    uint8_t OOBdataFlag;
    uint8_t AuthReq;
    uint8_t MaximumEncryptionKeySize;

    ble_key_distribution_t InitiatorKeyDistribution;

    ble_key_distribution_t ResponderKeyDistribution;
};
typedef struct _ble_smp_pairing_request_response_t ble_smp_pairing_request_response_t;



struct __attribute__((packed, aligned(1))) _ble_smp_pairing_confirm_random_t {
    uint8_t Data[16];
};
typedef struct _ble_smp_pairing_confirm_random_t ble_smp_pairing_confirm_random_t;


struct __attribute__((packed, aligned(1))) _ble_smp_pairing_failed_t {
    uint8_t Reason;
};
typedef struct _ble_smp_pairing_failed_t ble_smp_pairing_failed_t;





struct __attribute__((packed, aligned(1))) _ble_smp_key_t {
    uint8_t Key[16];
};
typedef struct _ble_smp_key_t ble_smp_key_t;


struct __attribute__((packed, aligned(1))) _ble_smp_master_identification_t {
    uint16_t EDIV;
    uint8_t Rand[8];
};
typedef struct _ble_smp_master_identification_t ble_smp_master_identification_t;


struct __attribute__((packed, aligned(1))) _ble_smp_identity_address_information_t {
    uint8_t AddrType;
    uint8_t BDA[6];
};
typedef struct _ble_smp_identity_address_information_t ble_smp_identity_address_information_t;


struct __attribute__((packed, aligned(1))) _ble_smp_security_request_t {
    uint8_t AuthReq;
};
typedef struct _ble_smp_security_request_t ble_smp_security_request_t;


struct __attribute__((packed, aligned(1))) _ble_smp_pairing_public_key_t {
    uint8_t PublicKeyX[32];
    uint8_t PublicKeyY[32];
};
typedef struct _ble_smp_pairing_public_key_t ble_smp_pairing_public_key_t;


struct __attribute__((packed, aligned(1))) _ble_smp_key_notification_t {
    uint8_t NotificationType;
};
typedef struct _ble_smp_key_notification_t ble_smp_key_notification_t;


struct __attribute__((packed, aligned(1))) _ble_smp_pdu_t {

    uint8_t Code;
    union __attribute__((packed, aligned(1))) {


        ble_smp_security_request_t sec_req;
        ble_smp_pairing_request_response_t pair_req;
        ble_smp_pairing_request_response_t pair_rsp;
        ble_smp_pairing_confirm_random_t pair_cfm;
        ble_smp_pairing_confirm_random_t pair_rnd;
        ble_smp_pairing_failed_t pair_err;
        ble_smp_key_t enc_key;
        ble_smp_key_t id_key;
        ble_smp_key_t sign_key;
        ble_smp_master_identification_t master_id;
        ble_smp_identity_address_information_t id_addr;


        ble_smp_key_t dhkey;
        ble_smp_key_notification_t key_ntf;
    } payload;
};
typedef struct _ble_smp_pdu_t ble_smp_pdu_t;

struct __attribute__((packed, aligned(1))) _ble_smp_pkt_t {
    ble_data_header_t header;
    ble_l2cap_header_t l2cap;
    ble_smp_pdu_t smp;
};
typedef struct _ble_smp_pkt_t ble_smp_pkt_t;
# 21 "../../../components/exble2/includes/core_ble.h" 2
# 1 "../../../components/exble2/includes/ble/ble_att.h" 1
# 17 "../../../components/exble2/includes/ble/ble_att.h"
typedef enum {
    ATT_Error_Response = 0x01,
    ATT_Exchange_MTU_Request = 0x02,
    ATT_Exchange_MTU_Response = 0x03,
    ATT_Find_Information_Request = 0x04,
    ATT_Find_Information_Response = 0x05,
    ATT_Find_By_Type_Value_Request = 0x06,
    ATT_Find_By_Type_Value_Response = 0x07,
    ATT_Read_By_Type_Request = 0x08,
    ATT_Read_By_Type_Response = 0x09,
    ATT_Read_Request = 0x0A,
    ATT_Read_Response = 0x0B,
    ATT_Read_Blob_Request = 0x0C,
    ATT_Read_Blob_Response = 0x0D,
    ATT_Read_Multiple_Request = 0x0E,
    ATT_Read_Multiple_Response = 0x0F,
    ATT_Read_by_Group_Type_Request = 0x10,
    ATT_Read_by_Group_Type_Response = 0x11,
    ATT_Write_Request = 0x12,
    ATT_Write_Response = 0x13,
    ATT_Write_command = 0x52,
    ATT_Prepare_Write_Request = 0x16,
    ATT_Prepare_Write_Response = 0x17,
    ATT_Execute_Write_Request = 0x18,
    ATT_Execute_Write_Response = 0x19,
    ATT_Handle_Value_Notification = 0x1B,
    ATT_Handle_Value_Indication = 0x1D,
    ATT_Handle_Value_Confirmation = 0x1E,
    ATT_Signed_Write_command = 0xD2,
} att_opcode_t;


typedef enum {
    ATT_ERR_NO_ERROR = 0x00,
    ATT_ERR_Invalid_Handle = 0x01,
    ATT_ERR_Read_Not_Permitted = 0x02,
    ATT_ERR_Write_Not_Permitted = 0x03,
    ATT_ERR_Invalid_PDU = 0x04,
    ATT_ERR_Insufficient_Authentication = 0x05,
    ATT_ERR_Request_Not_Supported = 0x06,
    ATT_ERR_Invalid_Offset = 0x07,
    ATT_ERR_Insufficient_Authorization = 0x08,
    ATT_ERR_Prepare_Queue_Full = 0x09,
    ATT_ERR_Attribute_Not_Found = 0x0A,
    ATT_ERR_Attribute_Not_Long = 0x0B,
    ATT_ERR_Insufficient_Encryption_Key_Size = 0x0C,
    ATT_ERR_Invalid_Attribute_Value_Length = 0x0D,
    ATT_ERR_Unlikely_Error = 0x0E,
    ATT_ERR_Insufficient_Encryption = 0x0F,
    ATT_ERR_Unsupported_Group_Type = 0x10,
    ATT_ERR_Insufficient_Resources = 0x11,
    ATT_ERR_Database_Out_Of_Sync = 0x12,
    ATT_ERR_Value_Not_Allowed = 0x13,
    ATT_ERR_Application_Error_Base = 0x80,
    ATT_ERR_Common_Profile_and_Service_Error_Base = 0xE0,
} att_error_code_t;



struct __attribute__((packed, aligned(1))) _ble_att_error_response_t {

    uint8_t RequestOpcode;

    uint16_t Handle;

    uint8_t ErrorCode;
};
typedef struct _ble_att_error_response_t ble_att_error_response_t;


struct __attribute__((packed, aligned(1))) _ble_att_exchange_mtu_request_t {

    uint16_t ClientRxMTU;
};
typedef struct _ble_att_exchange_mtu_request_t ble_att_exchange_mtu_request_t;

struct __attribute__((packed, aligned(1))) _ble_att_exchange_mtu_response_t {

    uint16_t ServerRxMTU;
};
typedef struct _ble_att_exchange_mtu_response_t ble_att_exchange_mtu_response_t;


struct __attribute__((packed, aligned(1))) _ble_att_find_information_request_t {

    uint16_t StartingHandle;

    uint16_t EndingHandle;
};
typedef struct _ble_att_find_information_request_t ble_att_find_information_request_t;


struct __attribute__((packed, aligned(1))) _ble_att_find_information_response_t {

    uint8_t Format;

    uint8_t InformationList[23-2];
};
typedef struct _ble_att_find_information_response_t ble_att_find_information_response_t;


struct __attribute__((packed, aligned(1))) _ble_att_find_by_type_request_t {

    uint16_t StartingHandle;

    uint16_t EndingHandle;

    uint8_t Type[2];

    uint8_t Value[23-7];
};
typedef struct _ble_att_find_by_type_request_t ble_att_find_by_type_request_t;


struct __attribute__((packed, aligned(1))) _ble_att_find_by_type_response_t {

    uint16_t HandlesInformationList[(23-1)/2];
};
typedef struct _ble_att_find_by_type_response_t ble_att_find_by_type_response_t;


struct __attribute__((packed, aligned(1))) _ble_att_read_by_type_request_t {

    uint16_t StartingHandle;

    uint16_t EndingHandle;

    uint8_t Type[16];
};
typedef struct _ble_att_read_by_type_request_t ble_att_read_by_type_request_t;


struct __attribute__((packed, aligned(1))) _ble_att_read_by_type_response_t {

    uint8_t Length;

    uint8_t DataList[23-2];
};
typedef struct _ble_att_read_by_type_response_t ble_att_read_by_type_response_t;


struct __attribute__((packed, aligned(1))) _ble_att_read_request_t {

    uint16_t Handle;
};
typedef struct _ble_att_read_request_t ble_att_read_request_t;


struct __attribute__((packed, aligned(1))) _ble_att_read_response_t {

    uint8_t Value[23-1];
};
typedef struct _ble_att_read_response_t ble_att_read_response_t;


struct __attribute__((packed, aligned(1))) _ble_att_read_blob_request_t {

    uint16_t Handle;

    uint16_t Offset;
};
typedef struct _ble_att_read_blob_request_t ble_att_read_blob_request_t;


struct __attribute__((packed, aligned(1))) _ble_att_read_blob_response_t {

    uint8_t PartValue[23-1];
};
typedef struct _ble_att_read_blob_response_t ble_att_read_blob_response_t;


struct __attribute__((packed, aligned(1))) _ble_att_read_by_group_type_request_t {

    uint16_t StartingHandle;

    uint16_t EndingHandle;

    uint8_t Type[16];
};
typedef struct _ble_att_read_by_group_type_request_t ble_att_read_by_group_type_request_t;


struct __attribute__((packed, aligned(1))) _ble_att_read_by_group_type_response_t {

    uint8_t Length;

    uint8_t DataList[23-2];
};
typedef struct _ble_att_read_by_group_type_response_t ble_att_read_by_group_type_response_t;


struct __attribute__((packed, aligned(1))) _ble_att_write_request_t {

    uint16_t Handle;




    uint8_t Value[23-3];

};
typedef struct _ble_att_write_request_t ble_att_write_request_t;







struct __attribute__((packed, aligned(1))) _ble_att_write_command_t {

    uint16_t Handle;




    uint8_t Value[23-3];

};
typedef struct _ble_att_write_command_t ble_att_write_command_t;


struct __attribute__((packed, aligned(1))) _ble_att_prepare_write_request_t {

  uint16_t Handle;

  uint16_t Offset;

  uint8_t PartValue[23-5];
};
typedef struct _ble_att_prepare_write_request_t ble_att_prepare_write_request_t;


struct __attribute__((packed, aligned(1))) _ble_att_prepare_write_response_t {

  uint16_t Handle;

  uint16_t Offset;

  uint8_t PartValue[23-5];
};
typedef struct _ble_att_prepare_write_response_t ble_att_prepare_write_response_t;


struct __attribute__((packed, aligned(1))) _ble_att_execute_write_request_t {


  uint8_t flags;
};
typedef struct _ble_att_execute_write_request_t ble_att_execute_write_request_t;


struct __attribute__((packed, aligned(1))) _ble_att_notification_indication_t {

    uint16_t Handle;

    uint8_t Value[23-3];
};
typedef struct _ble_att_notification_indication_t ble_att_notification_indication_t;

struct __attribute__((packed, aligned(1))) _ble_att_pdu_t {

    uint8_t Opcode;
    union __attribute__((packed, aligned(1))) {


        ble_att_exchange_mtu_request_t mtu_req;
        ble_att_exchange_mtu_response_t mtu_rsp;
        ble_att_error_response_t err_rsp;
        ble_att_find_information_request_t find_info_req;
        ble_att_find_information_response_t find_info_rsp;
        ble_att_find_by_type_request_t find_type_req;
        ble_att_find_by_type_response_t find_type_rsp;
        ble_att_read_by_type_request_t read_type_req;
        ble_att_read_by_type_response_t read_type_rsp;
        ble_att_read_request_t read_req;
        ble_att_read_response_t read_rsp;
        ble_att_read_blob_request_t read_blob_req;
        ble_att_read_blob_response_t read_blob_rsp;
        ble_att_read_by_group_type_request_t read_group_req;
        ble_att_read_by_group_type_response_t read_group_rsp;
        ble_att_write_request_t write_req;
        ble_att_prepare_write_request_t pre_write_req;
        ble_att_prepare_write_response_t pre_write_rsp;
        ble_att_execute_write_request_t exec_write_req;

        ble_att_write_command_t write_cmd;
        ble_att_notification_indication_t notify_indicate;
    } payload;
};
typedef struct _ble_att_pdu_t ble_att_pdu_t;

struct __attribute__((packed, aligned(1))) _ble_att_pkt_t {
    ble_data_header_t header;
    ble_l2cap_header_t l2cap;
    ble_att_pdu_t att;
};
typedef struct _ble_att_pkt_t ble_att_pkt_t;
# 22 "../../../components/exble2/includes/core_ble.h" 2
# 1 "../../../components/exble2/includes/ble/ble_gatts.h" 1
# 23 "../../../components/exble2/includes/core_ble.h" 2
# 1 "../../../components/exble2/includes/ble/ble_gap.h" 1
# 24 "../../../components/exble2/includes/core_ble.h" 2
# 19 "../../../components/exble2/includes\\ex2_api.h" 2
# 1 "../../../components/exble2/includes/ble/ble_services.h" 1
# 21 "../../../components/exble2/includes/ble/ble_services.h"
# 1 "../../../hal/device/include\\om_device.h" 1
# 13 "../../../hal/device/include\\om_device.h"
# 1 "../../../hal/device/include/../om6239/om6239.h" 1
# 55 "../../../hal/device/include/../om6239/om6239.h"
typedef enum IRQn {

    NonMaskableInt_IRQn = -14,
    HardFault_IRQn = -13,
    SVCall_IRQn = -5,
    PendSV_IRQn = -2,
    SysTick_IRQn = -1,


    RTC_IRQn = 0,
    USB_IRQn = 1,
    USB_WK_IRQn = 2,
    RF_IRQn = 3,
    WAKEUP_GPIO0_IRQn = 4,
    TIMER0_IRQn = 5,
    VBUS_IRQn = 6,
    WDT_IRQn = 7,
    SF0_IRQn = 8,
    ENCODER_IRQn = 9,
    RF_DMA_IRQn = 10,
    AES128_IRQn = 11,
    UART0_IRQn = 12,
    SENSCAN_IRQn = 13,
    LEDC_IRQn = 14,
} IRQn_Type;
# 92 "../../../hal/device/include/../om6239/om6239.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
# 114 "../../../hal/device/include/../om6239/om6239.h"
# 1 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 1
# 29 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
# 63 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
# 1 "../../../hal/CMSIS/Core/Include/cmsis_version.h" 1 3
# 29 "../../../hal/CMSIS/Core/Include/cmsis_version.h" 3
# 64 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 2 3
# 115 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
# 1 "../../../hal/CMSIS/Core/Include/cmsis_compiler.h" 1 3
# 47 "../../../hal/CMSIS/Core/Include/cmsis_compiler.h" 3
# 1 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 1 3
# 31 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
# 64 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

 struct __attribute__((packed)) T_UINT32 { uint32_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

 struct __attribute__((packed, aligned(1))) T_UINT16_WRITE { uint16_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

 struct __attribute__((packed, aligned(1))) T_UINT16_READ { uint16_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

 struct __attribute__((packed, aligned(1))) T_UINT32_WRITE { uint32_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

 struct __attribute__((packed, aligned(1))) T_UINT32_READ { uint32_t v; };
#pragma clang diagnostic pop
# 260 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U)
  {
    return op1;
  }
  return (op1 >> op2) | (op1 << (32U - op2));
}
# 295 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline uint8_t __CLZ(uint32_t value)
{
# 306 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
  if (value == 0U)
  {
    return 32U;
  }
  return __builtin_clz(value);
}
# 526 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline int32_t __SSAT(int32_t val, uint32_t sat)
{
  if ((sat >= 1U) && (sat <= 32U))
  {
    const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
    const int32_t min = -1 - max ;
    if (val > max)
    {
      return max;
    }
    else if (val < min)
    {
      return min;
    }
  }
  return val;
}
# 551 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline uint32_t __USAT(int32_t val, uint32_t sat)
{
  if (sat <= 31U)
  {
    const uint32_t max = ((1U << sat) - 1U);
    if (val > (int32_t)max)
    {
      return max;
    }
    else if (val < 0)
    {
      return 0U;
    }
  }
  return (uint32_t)val;
}
# 737 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline void __enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}
# 750 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline void __disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}
# 762 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline uint32_t __get_CONTROL(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}
# 792 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline void __set_CONTROL(uint32_t control)
{
  __asm volatile ("MSR control, %0" : : "r" (control) : "memory");
  __builtin_arm_isb(0xF);
}
# 818 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline uint32_t __get_IPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_APSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_xPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_PSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, psp" : "=r" (result) );
  return(result);
}
# 890 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline void __set_PSP(uint32_t topOfProcStack)
{
  __asm volatile ("MSR psp, %0" : : "r" (topOfProcStack) : );
}
# 914 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline uint32_t __get_MSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, msp" : "=r" (result) );
  return(result);
}
# 944 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}
# 995 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline uint32_t __get_PRIMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}
# 1025 "../../../hal/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static inline void __set_PRIMASK(uint32_t priMask)
{
  __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}
# 48 "../../../hal/CMSIS/Core/Include/cmsis_compiler.h" 2 3
# 116 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 2 3
# 199 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef union
{
  struct
  {
    uint32_t _reserved0:28;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} APSR_Type;
# 229 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:23;
  } b;
  uint32_t w;
} IPSR_Type;
# 247 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:15;
    uint32_t T:1;
    uint32_t _reserved1:3;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} xPSR_Type;
# 286 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef union
{
  struct
  {
    uint32_t _reserved0:1;
    uint32_t SPSEL:1;
    uint32_t _reserved1:30;
  } b;
  uint32_t w;
} CONTROL_Type;
# 314 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef struct
{
  volatile uint32_t ISER[1U];
        uint32_t RESERVED0[31U];
  volatile uint32_t ICER[1U];
        uint32_t RESERVED1[31U];
  volatile uint32_t ISPR[1U];
        uint32_t RESERVED2[31U];
  volatile uint32_t ICPR[1U];
        uint32_t RESERVED3[31U];
        uint32_t RESERVED4[64U];
  volatile uint32_t IP[8U];
} NVIC_Type;
# 341 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef struct
{
  volatile const uint32_t CPUID;
  volatile uint32_t ICSR;
        uint32_t RESERVED0;
  volatile uint32_t AIRCR;
  volatile uint32_t SCR;
  volatile uint32_t CCR;
        uint32_t RESERVED1;
  volatile uint32_t SHP[2U];
  volatile uint32_t SHCSR;
} SCB_Type;
# 448 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile const uint32_t CALIB;
} SysTick_Type;
# 623 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    __asm volatile("":::"memory");
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __asm volatile("":::"memory");
  }
}
# 642 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0U] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 661 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __builtin_arm_dsb(0xF);
    __builtin_arm_isb(0xF);
  }
}
# 680 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0U] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 699 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
# 714 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
# 732 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] = ((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2U)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] = ((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2U)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
}
# 756 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[ ( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2U)));
  }
  else
  {
    return((uint32_t)(((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2U)));
  }
}
# 781 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2U)) ? (uint32_t)(2U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(2U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2U));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority & (uint32_t)((1UL << (SubPriorityBits )) - 1UL)))
         );
}
# 808 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2U)) ? (uint32_t)(2U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(2U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2U));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority = (Priority ) & (uint32_t)((1UL << (SubPriorityBits )) - 1UL);
}
# 832 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)(16 << 2);
  *(vectors + (int32_t)IRQn) = vector;

}
# 848 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)(16 << 2);
  return *(vectors + (int32_t)IRQn);
}






__attribute__((__noreturn__)) static inline void __NVIC_SystemReset(void)
{
  __builtin_arm_dsb(0xF);

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = ((0x5FAUL << 16U) |
                 (1UL << 2U));
  __builtin_arm_dsb(0xF);

  for(;;)
  {
    __builtin_arm_nop();
  }
}
# 892 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline uint32_t SCB_GetFPUType(void)
{
    return 0U;
}
# 923 "../../../hal/CMSIS/Core/Include\\core_cm0.h" 3
static inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD = (uint32_t)(ticks - 1UL);
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 2U) - 1UL);
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL = 0UL;
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL = (1UL << 2U) |
                   (1UL << 1U) |
                   (1UL );
  return (0UL);
}
# 115 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/common_reg.h" 1
# 116 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/aes128_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/aes128_reg.h"
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t DATA[4];
    volatile uint32_t KEY[4];
    volatile uint32_t INT;
    volatile uint32_t INTMASK;
    volatile uint32_t SWAP;
} OM_AES128_Type;
# 117 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/rf_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/rf_reg.h"
typedef struct {
    volatile const uint32_t DMA_INT;
    volatile uint32_t DMA_INT_RAW;
    volatile uint32_t DMA_INT_MASK;
    volatile uint32_t DMA_CMD;
    volatile uint32_t DMA_ADDR;
    volatile uint32_t RFCE;
    volatile const uint32_t RX_PW;
    volatile uint32_t rsv1C;
    volatile uint32_t DFIFO_EN;
    volatile uint32_t CE_PULSE;

    volatile uint32_t ABORT;
    volatile uint32_t rsv2c[5];
    volatile uint32_t CONFIG;
    volatile uint32_t EN_AA;
    volatile uint32_t EN_RXADDR;
    volatile uint32_t SETUP_RETR;
    volatile uint32_t RF_CH;
    volatile uint32_t RF_SETUP;
    volatile uint32_t RF_STATUS;
    volatile uint32_t RSSI;
    union {
        volatile uint32_t RX_ADDR_P0;
        volatile uint32_t ACCESS_ADDR;
    };
    volatile uint32_t RX_ADDR_P0_H;
    volatile uint32_t RX_ADDR_P1;
    union {
        volatile uint32_t RX_ADDR_P2;
        volatile uint32_t BLE_CTL;
    };
    union {
        volatile uint32_t TX_ADDR;
        volatile uint32_t TX_ADVA;
    };
    union {
        volatile uint32_t TX_ADDR_H;
        volatile uint32_t TX_ADVA_H;
    };
    union {
        volatile uint32_t RX_PW_PIPE[3];
        volatile uint32_t TX_HEADER[3];
    };
    volatile const uint32_t FIFO_STATUS;
    volatile uint32_t DYNPD;
    volatile uint32_t FEATURE;
    volatile uint32_t SETUP_V;
    volatile uint32_t PRE_GURD;
    volatile const uint32_t RX_ADVA;
    volatile const uint32_t RX_ADVA_H;
    volatile const uint32_t RX_HEADER[3];
    volatile const uint32_t RX_STATUS[3];
    volatile const uint32_t DFIFO_STATUS;
    volatile uint32_t SETUP_DELAY;
    volatile uint32_t CRC_INIT;
    volatile uint32_t LINE;
    volatile uint32_t PLL_CTL0;
    volatile uint32_t PLL_CTL1;
    volatile uint32_t CAL_CTL;
    volatile uint32_t STATE;
    volatile uint32_t CHAN;
    volatile uint32_t FDEV;
    volatile uint32_t DAC_RANGE;
    volatile uint32_t CTUNING;
    volatile uint32_t FTUNING;
    volatile uint32_t RX_CTRL;
    volatile uint32_t rvF0;
    volatile uint32_t FAGC_CTRL_1;
    volatile uint32_t DOC_DACI;
    volatile uint32_t DOC_DACQ;
    volatile uint32_t AGC_CTRL;
    volatile uint32_t AGC_GAIN;
    volatile uint32_t RF_IVGEN;
    volatile uint32_t TEST_PKDET;
    volatile uint32_t rsv110;
    volatile uint32_t WHITELIST0;
    volatile uint32_t WHITELIST0_H;
    volatile uint32_t WHITELIST1;
    volatile uint32_t WHITELIST1_H;
    volatile uint32_t WHITELIST_CR;
    volatile uint32_t OBSERVE_TX;

    volatile uint32_t RX_CFO_EST;
    volatile uint32_t RX_DBG_CTRL;
} OM_RF_Type;
# 118 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/rtc_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/rtc_reg.h"
typedef struct {
    volatile uint32_t CR;
    volatile const uint32_t INTSTAT;
    volatile uint32_t INTRAWSTAT;
    volatile uint32_t INTMASK;
    volatile uint32_t TICK;
    volatile uint32_t ALARM0;
    volatile uint32_t CNT;
    volatile const uint32_t CNT_VALID;
    volatile const uint32_t CLKN_SYNC;
    volatile const uint32_t CLKN_VALID;
    volatile uint32_t ALARM1;
    volatile uint32_t ALARM2;
    volatile uint32_t WKRF_CR;
} OM_RTC_Type;
# 119 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/timer_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/timer_reg.h"
typedef struct {
    volatile uint32_t TINT;
    volatile uint32_t TINTMASK;
    volatile uint32_t TCON;
    volatile uint32_t TMOD;
    volatile uint32_t TH0;
    volatile uint32_t TL0;
    volatile uint32_t TDIV;
} OM_TIMER_Type;
# 120 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/pwm_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/pwm_reg.h"
typedef struct {
    volatile uint32_t PWMCON;
    volatile uint32_t PWMCR0;
    volatile uint32_t PWMCR1;
    volatile uint32_t PWMDIV;
    volatile uint32_t PWMPRD;
    union {
        volatile uint32_t PWMDC[8];
        struct {
            volatile uint32_t PWMDC0;
            volatile uint32_t PWMDC1;
            volatile uint32_t PWMDC2;
            volatile uint32_t PWMDC3;
            volatile uint32_t PWMDC4;
            volatile uint32_t PWMDC5;
            volatile uint32_t PWMDC6;
            volatile uint32_t PWMDC7;
        };
    };
} OM_PWM_Type;
# 121 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/usb_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/usb_reg.h"
typedef struct {

  volatile uint8_t FADDR;
  volatile uint8_t POWER;
  volatile uint8_t INTR_TX1;
  volatile uint8_t INTR_TX2;
  volatile uint8_t INTR_RX1;
  volatile uint8_t INTR_RX2;
  volatile uint8_t INTR_USB;
  volatile uint8_t INTR_TXEN1;
  volatile uint8_t INTR_TXEN2;
  volatile uint8_t INTR_RXEN1;
  volatile uint8_t INTR_RXEN2;
  volatile uint8_t INTR_USBEN;
  volatile uint8_t FRAME1;
  volatile uint8_t FRAME2;
  volatile uint8_t INDEX;
  volatile uint8_t DEVCTL;

  volatile uint8_t TXMAXP;
  union
  {
    volatile uint8_t CSR0;
    volatile uint8_t TXCSR1;
  };
  union
  {
    volatile uint8_t CSR02;
    volatile uint8_t TXCSR2;
  };
  volatile uint8_t RXMAXP;
  volatile uint8_t RXCSR1;
  volatile uint8_t RXCSR2;
  union
  {
    volatile uint8_t COUNT0;
    volatile uint8_t RXCOUNT1;
  };
  volatile uint8_t RXCOUNT2;
  volatile uint8_t x18_1e[7];
  volatile uint8_t FIFOSIZE;

  volatile uint32_t EPnFIFO[16];
       uint8_t x60_1ff[0x200-0x60];

  volatile uint32_t DMA_INTR;

} OM_USB_Type;
# 122 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/hcache_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/hcache_reg.h"
typedef struct {
     volatile const uint32_t TYPE;
     volatile uint32_t CONFIG;
     volatile uint32_t CTRL;
     volatile uint32_t STATUS;
          uint32_t RESERVE0[4];
     volatile uint32_t MAINT0;
     volatile uint32_t MAINT1;
     volatile uint32_t MON_CONFIG;
     volatile uint32_t MON_EN;
     volatile uint32_t MON_CTRL;
     volatile uint32_t MON_STATUS;
} OM_ICACHE_Type;
# 123 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/flash_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/flash_reg.h"
typedef struct {
    volatile const uint32_t INTR_STATUS;
    volatile uint32_t RAW_INTR_STATUS;
    volatile uint32_t INTR_MASK;
    volatile uint32_t COMMAND;
    volatile uint32_t COMMAND_DATA0_REG;
    volatile uint32_t COMMAND_DATA1_REG;
    volatile uint32_t ADDRESS_REG;
    volatile uint32_t READ_OPCODE_REG;
    volatile uint32_t CONFIGURATION_0;
    volatile uint32_t CONFIGURATION_1;
    volatile uint32_t WP_HOLD_REG;
} OM_FLASH_Type;
# 124 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/rcc_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/rcc_reg.h"
typedef struct {
    volatile uint32_t CLKCTRL;
    volatile uint32_t CLKGATE;
    volatile uint32_t RSTCTRL;
    volatile uint32_t M0CALIB;
    volatile uint32_t SYSCLK_SEL;




    volatile uint32_t rsv_x14;

    volatile uint32_t FLASH_CLKCTRL;
    volatile uint32_t FLASH_READ_OPCODE;
    volatile uint32_t FLASH_OFFSET;
    volatile uint32_t USB_CTRL;
    volatile uint32_t USB_WK_INT_CLR;
    volatile uint32_t USB_WK_SIG_SEL;
    volatile uint32_t USB_WK_CLK_SEL;
} OM_RCC_Type;
# 125 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/uart_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/uart_reg.h"
typedef struct {
    volatile uint32_t INTR_STATUS;
    volatile uint32_t INTR_MASK;
    volatile uint32_t SCON;
    volatile uint32_t SMOD;
    volatile uint32_t SREL;
    volatile uint32_t SBUF;
    volatile uint32_t FIFO_TH;
    volatile uint32_t FIFO_ST;
} OM_UART_Type;
# 126 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/wdt_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/wdt_reg.h"
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t SV;
} OM_WDT_Type;
# 127 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/gpio_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/gpio_reg.h"
typedef struct {
    volatile uint32_t DATA;
    volatile uint32_t DATAOUT;



    volatile uint32_t DATAOUTSET;
    volatile uint32_t DATAOUTCLR;

    volatile uint32_t OUTENSET;
    volatile uint32_t OUTENCLR;
         uint32_t rsv_x18_x1c[2];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t INTTYPE0SET;
    volatile uint32_t INTTYPE0CLR;
    volatile uint32_t INTPOLSET;
    volatile uint32_t INTPOLCLR;
    volatile uint32_t INTSTATUS;
    volatile uint32_t rsv_x3c;
    volatile uint32_t INTTYPE1SET;
    volatile uint32_t INTTYPE1CLR;





} OM_GPIO_Type;
# 128 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/../common/pof_reg.h" 1
# 64 "../../../hal/device/include/../om6239/../common/pof_reg.h"
typedef struct {
    volatile uint32_t rsv_x00_x3C[16];
    volatile uint32_t POFCON;
    volatile uint32_t POFMSK;
    volatile uint32_t DRV_CTRL;
} OM_POF_Type;
# 129 "../../../hal/device/include/../om6239/om6239.h" 2

# 1 "../../../hal/device/include/../om6239/pmu_reg.h" 1
# 64 "../../../hal/device/include/../om6239/pmu_reg.h"
typedef struct {
    volatile uint32_t BOOT_MODE;
    volatile uint32_t CLK32K_SEL;
    volatile uint32_t CLKLP_CTRL;
    volatile uint32_t ANA_CTRL;
    volatile uint32_t LPMS;
    volatile uint32_t WKINT_CLR;
    volatile uint32_t PLL_CTRL;
    volatile uint32_t PLL_CTRL1;
    volatile uint32_t rsv_x20;
    volatile uint32_t DELAY_CTRL;
    volatile uint32_t PINMUX_SEL;
    volatile uint32_t RF_DEBUG;
    volatile uint32_t FLASH_PWR_CMD;
    volatile uint32_t rsv_x34_x3c[3];
    volatile uint32_t PAD_WK_CTRL;
    volatile uint32_t PAD_WK_CTRL_1;
    volatile uint32_t PAD_BUF_EN;
    volatile uint32_t PAD_PD_CTRL;
    volatile uint32_t PAD_PU_CTRL;
    volatile uint32_t PAD_PU_CTRL_1;
    volatile uint32_t PAD_DRV_CTRL;
    volatile uint32_t PAD_DRV_CTRL_1;
    volatile uint32_t rsv_x60_x68[3];
    union {
        volatile uint32_t SW_RSVD0;
        volatile uint32_t CPU_CONTEXT_ADDR;
    };
    volatile uint32_t SW_RSVD1;
    volatile uint32_t SW_RSVD2;
    volatile uint32_t SW_RSVD3;
    volatile uint32_t SW_RSVD4;
    volatile uint32_t SW_RSVD5;
    volatile uint32_t SW_RSVD6;
    volatile uint32_t SW_RSVD7;
} OM_PMU_Type;
# 131 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/senscan_reg.h" 1
# 64 "../../../hal/device/include/../om6239/senscan_reg.h"
typedef struct {
     volatile uint32_t CSR;
     volatile uint32_t ISR;
     volatile uint32_t IER;
     union {
          uint32_t ADDR_REG[7];
          struct {
               volatile uint32_t IDADDR;
               volatile uint32_t ID;
               volatile uint32_t MOADDR;
               volatile uint32_t XADDR;
               volatile uint32_t YADDR;
               volatile uint32_t HADDR1;
               volatile uint32_t HADDR2;
          };
     };
     volatile const uint32_t X_DATA;
     volatile const uint32_t Y_DATA;
     volatile uint32_t TR;
     volatile uint32_t TNS;
     volatile uint32_t SCAN_FREQ;
     volatile uint32_t RESYNC;
     volatile uint32_t CFG_CSR;
     volatile uint32_t CFG_ADDR;
     volatile uint32_t CFG_DATA;
} OM_SENSCAN_Type;
# 132 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/encoder_reg.h" 1
# 64 "../../../hal/device/include/../om6239/encoder_reg.h"
typedef struct {
     volatile uint32_t EN;
     volatile uint32_t CNT;
     volatile uint32_t MODE;
     volatile uint32_t SAM;
     volatile uint32_t DBG;
     volatile uint32_t VALID;
} OM_ENCODER_Type;
# 133 "../../../hal/device/include/../om6239/om6239.h" 2
# 1 "../../../hal/device/include/../om6239/ledc_reg.h" 1
# 64 "../../../hal/device/include/../om6239/ledc_reg.h"
typedef struct {
     volatile uint32_t CR;
     volatile uint32_t SIG_TIM;
     volatile uint32_t RST_TIM;
     volatile uint32_t DMA_CTL;
} OM_LEDC_Type;
# 134 "../../../hal/device/include/../om6239/om6239.h" 2
# 182 "../../../hal/device/include/../om6239/om6239.h"
#pragma clang diagnostic pop
# 14 "../../../hal/device/include\\om_device.h" 2
# 22 "../../../components/exble2/includes/ble/ble_services.h" 2
# 31 "../../../components/exble2/includes/ble/ble_services.h"
typedef uint16_t ble_cccd_t;
# 41 "../../../components/exble2/includes/ble/ble_services.h"
typedef enum {
    BLE_DIS_VID_SOURCE_SIG = 0x01,
    BLE_DIS_VID_SORUCE_USB = 0x02,
} ble_dis_vid_source_t;
# 53 "../../../components/exble2/includes/ble/ble_services.h"
typedef struct __attribute__((packed, aligned(1))) {
    ble_dis_vid_source_t vid_source;
    uint16_t vid;
    uint16_t pid;
    uint16_t prod_ver;
} ble_dis_pnp_t;
# 68 "../../../components/exble2/includes/ble/ble_services.h"
typedef enum {
    BLE_HID_PROTOCOL_MODE_BOOL = 0,
    BLE_HID_PROTOCOL_MODE_REPORT = 1,
} ble_hid_protocol_mode_t;
# 80 "../../../components/exble2/includes/ble/ble_services.h"
typedef enum {
    BLE_HID_REPORT_TYPE_INPUT = 1,
    BLE_HID_REPORT_TYPE_OUTPUT = 2,
    BLE_HID_REPORT_TYPE_FEATURE = 3,
} ble_hid_report_type_t;
# 109 "../../../components/exble2/includes/ble/ble_services.h"
typedef struct {
    uint8_t report_id;
    ble_hid_report_type_t report_type;
} ble_hid_report_ref_t;
# 121 "../../../components/exble2/includes/ble/ble_services.h"
typedef struct {
    uint16_t bcdHID;
    uint8_t bCountryCode;
    uint8_t RemoteWake : 1;
    uint8_t NormallyConnectable : 1;
} ble_hid_info_t;
# 135 "../../../components/exble2/includes/ble/ble_services.h"
typedef enum {
    BLE_HID_CTRL_POINT_ENTER_SUSPEND = 0,
    BLE_HID_CTRL_POINT_EXIT_SUSPEND = 1,
} ble_hid_ctrl_point_t;
# 20 "../../../components/exble2/includes\\ex2_api.h" 2
# 70 "../../../components/exble2/includes\\ex2_api.h"
typedef enum {
    EXE_LINK_STATE_STANDBY = 0U,
    EXE_LINK_STATE_ADV = 1U,
    EXE_LINK_STATE_CONN = 2U,
    EXE_LINK_STATE_SCAN = 3U,
    EXE_LINK_STATE_INIT = 4U,



} exe_stk_state_t;
# 99 "../../../components/exble2/includes\\ex2_api.h"
typedef void (*ex2_evt_app_handler_t)(uint32_t events);
# 114 "../../../components/exble2/includes\\ex2_api.h"
typedef att_error_code_t (*ex2_att_app_handler_t)(uint16_t offset, uint8_t *payload, uint16_t len);





typedef enum {
    EX2_UUID_LEN_2B = 0,
    EX2_UUID_LEN_16B = 1,
} ex2_uuid_len_t;
# 132 "../../../components/exble2/includes\\ex2_api.h"
typedef enum {
    EX2_ATT_VALUE_TYPE_DATA = 0,
    EX2_ATT_VALUE_TYPE_PTR = 1,
    EX2_ATT_VALUE_TYPE_FUNC = 2,
} ex2_att_value_type_t;
# 148 "../../../components/exble2/includes\\ex2_api.h"
typedef struct {
    uint8_t rsvd : 1;
    uint8_t uuid_len : 1;
    uint8_t permission : 4;
    uint8_t value_type : 2;
    uint8_t value_len;
    uint16_t uuid_idx;
    uint32_t value;
} exe_att_ent_t;
# 176 "../../../components/exble2/includes\\ex2_api.h"
typedef struct {
    uint16_t interval_min;
    uint16_t interval_max;
    uint16_t latency;
    uint16_t timeout;
} ex2_gap_ppcp_t;





typedef struct ex2_data {
    uint8_t *data;
    uint8_t len;
} ex2_data_t;





extern exe_stk_state_t exe_stk_state;


extern const exe_att_ent_t ex2_tbl_gatt_database[] __attribute__((weak));

extern const uint8_t ex2_profile_uuids_set_vendor[][16] __attribute__((weak));
# 210 "../../../components/exble2/includes\\ex2_api.h"
void ex2_stk_init(const uint8_t *bd_addr);




void ex2_stk_register_app_evt_handler(ex2_evt_app_handler_t evt_app_hander);




void ex2_stk_uninit(void);




uint8_t *ex2_stk_txq_dequeue(void);





void ex2_stk_wakeup(void);





void ex2_stk_process(void);






_Bool ex2_stk_interrupt(void);






uint32_t ex2_stk_sleep_duration_get(void);







uint8_t ex2_stk_get_txq_num(void);
uint8_t ex2_stk_get_rxq_num(void);






uint16_t ex2_ll_get_conn_event_counter(void);





uint32_t ex2_ll_get_conn_interval_tick(void);
# 285 "../../../components/exble2/includes\\ex2_api.h"
_Bool ex2_l2cap_update_conn_para(const ex2_gap_ppcp_t *ppcp);
# 296 "../../../components/exble2/includes\\ex2_api.h"
_Bool ex2_l2cap_create_le_conn(uint16_t psm, uint16_t scid);





void ex2_gap_disable_latency(void);





void ex2_gap_enable_latency(void);
# 324 "../../../components/exble2/includes\\ex2_api.h"
_Bool ex2_gap_set_broadcast_mode(const ex2_data_t *adv_pkt, const ex2_data_t *adv_rsp_pkt, uint8_t is_disc, int adv_interval_ms, uint32_t adv_timeout_ms);





void ex2_gap_disconnectd(void);






extern void ex2_smp_enable_bond(void);
# 348 "../../../components/exble2/includes\\ex2_api.h"
uint8_t ex2_att_tx_notification(uint16_t handle, uint8_t *p_data, int len);
# 359 "../../../components/exble2/includes\\ex2_api.h"
uint8_t ex2_att_tx_indication(uint16_t handle, uint8_t *p_data, int len);
# 372 "../../../components/exble2/includes\\ex2_api.h"
void ex2_att_execute_write_callback(uint16_t handle, _Bool write_en);
# 382 "../../../components/exble2/includes\\ex2_api.h"
void ex2_att_indication_confirm_callback(uint16_t handle);







uint32_t ex2_att_discovery_completed_timeout_get(void);







void ex2_ll_set_next_polling_time(_Bool sync_latency);





void ex2_ll_polling_time_start(void);





void ex2_ll_polling_time_stop(void);
# 420 "../../../components/exble2/includes\\ex2_api.h"
_Bool ex2_ll_hci_report_adv_packet(uint8_t *adv_pkt);
# 437 "../../../components/exble2/includes\\ex2_api.h"
void ex2_ll_hci_connect_param_update_complete(uint8_t *buf);







_Bool ex2_ll_hci_rx_enc_req_process(uint8_t *param);





_Bool ex2_ll_hci_ev_encrypt_chg(void);
# 464 "../../../components/exble2/includes\\ex2_api.h"
void ex2_att_execute_write_callback(uint16_t handle, _Bool write_en);
# 474 "../../../components/exble2/includes\\ex2_api.h"
void ex2_att_indication_confirm_callback(uint16_t handle);
# 16 "../main/ex2_profile_hid_mouse.c" 2
# 1 "../main/ex2_app_mouse.h" 1
# 37 "../main/ex2_app_mouse.h"
typedef enum {
    ATT_HANDLE_BEGIN = 0,


    ATT_HANDLE_GAP_PS,
    ATT_HANDLE_GAP_DEVNAME_CD,
    ATT_HANDLE_GAP_DEVNAME_CV,
    ATT_HANDLE_GAP_APPEARANCE_CD,
    ATT_HANDLE_GAP_APPEARANCE_CV,
    ATT_HANDLE_GAP_PPCP_CD,
    ATT_HANDLE_GAP_PPCP_CV,



    ATT_HANDLE_GATT_PS,
    ATT_HANDLE_GATT_SCC_CD,
    ATT_HANDLE_GATT_SCC_CV,
    ATT_HANDLE_GATT_SCC_CCCD,




    ATT_HANDLE_DIS_PS,
    ATT_HANDLE_DIS_PNP_CD,
    ATT_HANDLE_DIS_PNP_CV,




    ATT_HANDLE_BAS_PS,
    ATT_HANDLE_BAS_BAT_LVL_CD,
    ATT_HANDLE_BAS_BAT_LVL_CV,
    ATT_HANDLE_BAS_BAT_LVL_CCCD,




    ATT_HANDLE_HID_PS,
    ATT_HANDLE_HID_PROTOCOL_MODE_CD,
    ATT_HANDLE_HID_PROTOCOL_MODE_CV,
# 85 "../main/ex2_app_mouse.h"
    ATT_HANDLE_HID_MOUSE_REPORT_CD,
    ATT_HANDLE_HID_MOUSE_REPORT_CV,
    ATT_HANDLE_HID_MOUSE_REPORT_CCD,
    ATT_HANDLE_HID_MOUSE_REPORT_RRD,



    ATT_HANDLE_HID_CONSUMER_CONTROL_REPORT_CD,
    ATT_HANDLE_HID_CONSUMER_CONTROL_REPORT_CV,
    ATT_HANDLE_HID_CONSUMER_CONTROL_REPORT_CCD,
    ATT_HANDLE_HID_CONSUMER_CONTROL_REPORT_RRD,
# 107 "../main/ex2_app_mouse.h"
    ATT_HANDLE_HID_KEYBOARD_IN_REPORT_CD,
    ATT_HANDLE_HID_KEYBOARD_IN_REPORT_CV,
    ATT_HANDLE_HID_KEYBOARD_IN_REPORT_CCD,
    ATT_HANDLE_HID_KEYBOARD_IN_REPORT_RRD,

    ATT_HANDLE_HID_KEYBOARD_OUT_REPORT_CD,
    ATT_HANDLE_HID_KEYBOARD_OUT_REPORT_CV,
    ATT_HANDLE_HID_KEYBOARD_OUT_REPORT_RRD,



    ATT_HANDLE_BITMAP_KEYBOARD_REPORT_CD,
    ATT_HANDLE_BITMAP_KEYBOARD_REPORT_CV,
    ATT_HANDLE_BITMAP_KEYBOARD_REPORT_CCD,
    ATT_HANDLE_BITMAP_KEYBOARD_REPORT_RRD,


    ATT_HANDLE_HID_REPORT_MAP_CD,
    ATT_HANDLE_HID_REPORT_MAP_CV,

    ATT_HANDLE_HID_INFORMATION_CD,
    ATT_HANDLE_HID_INFORMATION_CV,

    ATT_HANDLE_HID_CONTROL_POINT_CD,
    ATT_HANDLE_HID_CONTROL_POINT_CV,
# 142 "../main/ex2_app_mouse.h"
    ATT_HANDLE_END,
} att_handles_set_t;
# 157 "../main/ex2_app_mouse.h"
extern void ex2_app_mouse_ble_init(void);
# 168 "../main/ex2_app_mouse.h"
extern void hid_notification_enable(uint16_t hid_cccd);
# 177 "../main/ex2_app_mouse.h"
extern uint16_t hid_notification_is_enabled(void);
# 186 "../main/ex2_app_mouse.h"
extern uint8_t ex2_app_mouse_scan(void);
# 17 "../main/ex2_profile_hid_mouse.c" 2
# 1 "../main/mouse.h" 1



typedef enum {
    MS_SLEEP_LEVEL0 = 0U,
    MS_SLEEP_LEVEL1 = 1U,
    MS_SLEEP_LEVEL2 = 2U,
} ms_sleep_level_t;







typedef enum {
    MOUSE_LE_STATE_ADV = 0,
    MOUSE_LE_STATE_ADV_SWIFT = 1,
    MOUSE_LE_STATE_DISCONN_ADV= 2,
    MOUSE_LE_STATE_DISCONN = 3,
    MOUSE_LE_STATE_STOP = 4,
} mouse_adv_state_t;
# 37 "../main/mouse.h"
extern char bt_kb_name[29U];

extern void ex2_app_mouse_init(void);
extern void app_ble_evt_dispatch(uint32_t events);
extern void ex2_app_mouse_broadcast_fsm(void);
# 18 "../main/ex2_profile_hid_mouse.c" 2




extern uint8_t kb_led_status;



ex2_gap_ppcp_t ex2_gap_ppcp_value = {
    .interval_min = 6,
    .interval_max = 6,
    .latency = 44,
    .timeout = 216,
};



static uint16_t _gatt_service_changed_value[4] = {0};
static uint16_t _gatt_service_changed_cccd_value = 0;





static const ble_dis_pnp_t _dis_pnp_value = {
    .vid_source = BLE_DIS_VID_SORUCE_USB,
    .vid = 0x32C2,
    .pid = 0x0029,
    .prod_ver = (((1) << 8) + (0)),
};




static uint8_t _bas_bat_lvl_value = 100;
static uint16_t _bas_cccd_value;
# 62 "../main/ex2_profile_hid_mouse.c"
_Bool profile_bas_tx_notification(uint8_t level)
{
    _bas_bat_lvl_value = level;
    _bas_cccd_value=0x01;
    if (_bas_cccd_value & 0x01 ) {
        return ex2_att_tx_notification(ATT_HANDLE_BAS_BAT_LVL_CV, &level, 1);
    }
    return 0;
}





typedef enum {
    HID_REPORT_ID_MOUSE_INPUT = 1,
    HID_REPORT_ID_CONSUMER_CONTROL_INPUT = 2,
    HID_REPORT_ID_KEYBOARD_INPUT = 3,
    HID_REPORT_ID_BITMAP_KB_INPUT = 4,
} hid_report_id_t;


static ble_hid_protocol_mode_t _hid_protocol_mode_value = BLE_HID_PROTOCOL_MODE_REPORT;
static uint16_t _hid_cccd_value;


static const ble_hid_info_t _hid_info_value = {
    .bcdHID = 0x111,
    .bCountryCode = 0,
    .RemoteWake = 0,
    .NormallyConnectable = 1,
};



static uint8_t hid_mouse_report_value[6];




static uint8_t hid_consumer_control_report_value[2];




static uint8_t hid_keyboard_in_report_value[8];
static uint8_t bitmap_keyboard_report_value[15];
uint8_t hid_keyboard_out_report_value;


static const uint8_t _hid_report_map_value[] = {

    0x05, 0x01,
    0x09, 0x06,
    0xA1, 0x01,
    0x85, HID_REPORT_ID_KEYBOARD_INPUT,
    0x05, 0x07,
    0x19, 0xe0,
    0x29, 0xe7,
    0x15, 0x00,
    0x25, 0x01,
    0x75, 0x01,
    0x95, 0x08,
    0x81, 0x02,
    0x95, 0x01,
    0x75, 0x08,
    0x81, 0x01,

    0x05, 0x07,
    0x95, 0x05,
    0x75, 0x01,
    0x05, 0x08,
    0x19, 0x01,
    0x29, 0x05,
    0x91, 0x02,
    0x95, 0x01,
    0x75, 0x03,
    0x91, 0x01,

    0x95, 0x06,
    0x75, 0x08,
    0x15, 0x00,
    0x25, 0xff,
    0x05, 0x07,
    0x19, 0x00,
    0x29, 0xFF,
    0x81, 0x00,
    0xC0,



    0x05 , 0x0C,
    0x09 , 0x01,
    0xA1 , 0x01,
    0x85 , HID_REPORT_ID_CONSUMER_CONTROL_INPUT,
    0x15 , 0x00,
    0x26 , 0xff, 0x03,
    0x19 , 0x00,
    0x2A , 0xff, 0x03,
    0x75 , 0x10,
    0x95 , 0x01,
    0x81 , 0x00,
    0xC0 ,



    0x05, 0x01,
    0x09, 0x06,
    0xA1, 0x01,
    0x85, HID_REPORT_ID_BITMAP_KB_INPUT,
    0x05, 0x07,
    0x19, 0x00,
    0x29, 0x77,
    0x15, 0x00,
    0x25, 0x01,
    0x95, 0x78,
    0x75, 0x01,
    0x81, 0x02,
    0xC0,



    0x05, 0x01,
    0x09, 0x02,
    0xA1, 0x01,
    0x85, HID_REPORT_ID_MOUSE_INPUT,
    0x09, 0x01,
    0xA1, 0x00,
    0x05, 0x09,
    0x19, 0x01,
    0x29, 0x08,
    0x15, 0x00,
    0x25, 0x01,
    0x95, 0x08,
    0x75, 0x01,
    0x81, 0x02,
    0x05, 0x01,
    0x09, 0x30,
    0x09, 0x31,
    0x16, 0x01, 0xF8,
    0x26, 0xFF, 0x07,
    0x75, 0x0C,
    0x95, 0x02,
    0x81, 0x06,
    0x09, 0x38,
    0x15, 0x81,
    0x25, 0x7F,
    0x75, 0x08,
    0x95, 0x01,
    0x81, 0x06,
    0x05, 0x0C,
    0x0A, 0x38, 0x02,
    0x95, 0x01,
    0x81, 0x06,
    0xC0,
    0xC0,

};







_Bool ex2_hid_tx_notification_mouse(uint8_t *buf)
{
    if(ex2_stk_get_txq_num() <= (3))
    {
        return ex2_att_tx_notification(ATT_HANDLE_HID_MOUSE_REPORT_CV, buf, 6);
    }
    else
        return 0;
}

_Bool ex2_hid_tx_notification_keyboard(uint8_t *buf)
{
    if(ex2_stk_get_txq_num() <= (3))
        return ex2_att_tx_notification(ATT_HANDLE_HID_KEYBOARD_IN_REPORT_CV, buf, 8);
    else
        return 0;
}

uint8_t ex2_hid_rx_command_keyboard(void)
{
    return kb_led_status;
}

_Bool ex2_hid_tx_notification_bitmap_kb(uint8_t *buf)
{
    if(ex2_stk_get_txq_num() <= (3))
        return ex2_att_tx_notification(ATT_HANDLE_BITMAP_KEYBOARD_REPORT_CV, buf, 15);
    else
        return 0;
}

_Bool ex2_hid_tx_notification_consumer_control(uint8_t *buf)
{
    if(ex2_stk_get_txq_num() <= (3))
    {
        return ex2_att_tx_notification(ATT_HANDLE_HID_CONSUMER_CONTROL_REPORT_CV, buf, 2);
    }
    else
        return 0;
}

void hid_notification_enable(uint16_t hid_cccd)
{
    _hid_cccd_value = hid_cccd;
    _bas_cccd_value = hid_cccd;
}

uint16_t hid_notification_is_enabled(void)
{
    return _hid_cccd_value & 0x01;
}

att_error_code_t hid_control_point_write(uint16_t offset, uint8_t *payload, uint16_t len)
{
    ble_hid_ctrl_point_t ctrl_point;
    ctrl_point = payload[0];

    return ATT_ERR_NO_ERROR;
}
# 301 "../main/ex2_profile_hid_mouse.c"
const exe_att_ent_t ex2_tbl_gatt_database[] = {

    { .rsvd = 0, .uuid_len = (0), .uuid_idx = (0), .value_type = (0), .value_len = (0), .value = (uint32_t)(ATT_HANDLE_END-1), .permission = (0), },


    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2800), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (2), .value = (uint32_t)(0x1800), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A00), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (29U), .value = (uint32_t)(bt_kb_name), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A01), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (2), .value = (uint32_t)(961), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A04), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (sizeof(ex2_gap_ppcp_value)), .value = (uint32_t)(&ex2_gap_ppcp_value), .permission = ((1U << 0)), },



    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2800), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (2), .value = (uint32_t)(0x1801), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x20), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A05), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (4), .value = (uint32_t)(&_gatt_service_changed_value[0]), .permission = ((1U << 0) | (1U << 1)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2902), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (2), .value = (uint32_t)(&_gatt_service_changed_cccd_value), .permission = ((1U << 0) | (1U << 1)), },




    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2800), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (2), .value = (uint32_t)(0x180A), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A50), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (sizeof(ble_dis_pnp_t)), .value = (uint32_t)(&_dis_pnp_value), .permission = ((1U << 0)), },




    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2800), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (2), .value = (uint32_t)(0x180F), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02 | 0x10), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A19), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (1), .value = (uint32_t)(&_bas_bat_lvl_value), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2902), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (2), .value = (uint32_t)(&_bas_cccd_value), .permission = ((1U << 0) | (1U << 1) | (1U << 3)), },




    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2800), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (2), .value = (uint32_t)(0x1812), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02 | 0x04), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A4E), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (1), .value = (uint32_t)(&_hid_protocol_mode_value), .permission = ((1U << 0) | (1U << 1)), },
# 352 "../main/ex2_profile_hid_mouse.c"
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02 | 0x10), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A4D), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (sizeof(hid_mouse_report_value)), .value = (uint32_t)(&hid_mouse_report_value[0]), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2902), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (2), .value = (uint32_t)(&_hid_cccd_value), .permission = ((1U << 0) | (1U << 1) | (1U << 3)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2908), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (sizeof(ble_hid_report_ref_t)), .value = (uint32_t)((((HID_REPORT_ID_MOUSE_INPUT) & 0xFFU) + (((BLE_HID_REPORT_TYPE_INPUT) & 0xFFU) << 8))), .permission = ((1U << 0)), },




    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02 | 0x10), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A4D), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (sizeof(hid_consumer_control_report_value)), .value = (uint32_t)(&hid_consumer_control_report_value[0]), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2902), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (2), .value = (uint32_t)(&_hid_cccd_value), .permission = ((1U << 0) | (1U << 1) | (1U << 3)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2908), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (sizeof(ble_hid_report_ref_t)), .value = (uint32_t)((((HID_REPORT_ID_CONSUMER_CONTROL_INPUT) & 0xFFU) + (((BLE_HID_REPORT_TYPE_INPUT) & 0xFFU) << 8))), .permission = ((1U << 0)), },
# 379 "../main/ex2_profile_hid_mouse.c"
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02 | 0x10), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A4D), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (sizeof(hid_keyboard_in_report_value)), .value = (uint32_t)(&hid_keyboard_in_report_value[0]), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2902), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (2), .value = (uint32_t)(&_hid_cccd_value), .permission = ((1U << 0) | (1U << 1) | (1U << 3)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2908), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (sizeof(ble_hid_report_ref_t)), .value = (uint32_t)((((HID_REPORT_ID_KEYBOARD_INPUT) & 0xFFU) + (((BLE_HID_REPORT_TYPE_INPUT) & 0xFFU) << 8))), .permission = ((1U << 0)), },


    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02 | 0x08 | 0x04), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A4D), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (1), .value = (uint32_t)(&hid_keyboard_out_report_value), .permission = ((1U << 0) | (1U << 1) | (1U << 3)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2908), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (sizeof(ble_hid_report_ref_t)), .value = (uint32_t)((((HID_REPORT_ID_KEYBOARD_INPUT) & 0xFFU) + (((BLE_HID_REPORT_TYPE_OUTPUT) & 0xFFU) << 8))), .permission = ((1U << 0)), },




    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02 | 0x10), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A4D), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (sizeof(bitmap_keyboard_report_value)), .value = (uint32_t)(&bitmap_keyboard_report_value[0]), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2902), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (2), .value = (uint32_t)(&_hid_cccd_value), .permission = ((1U << 0) | (1U << 1) | (1U << 3)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2908), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (sizeof(ble_hid_report_ref_t)), .value = (uint32_t)((((HID_REPORT_ID_BITMAP_KB_INPUT) & 0xFFU) + (((BLE_HID_REPORT_TYPE_INPUT) & 0xFFU) << 8))), .permission = ((1U << 0)), },



    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A4B), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (sizeof(_hid_report_map_value)), .value = (uint32_t)(&_hid_report_map_value[0]), .permission = ((1U << 0) | (1U << 3)), },


    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x02), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A4A), .value_type = (EX2_ATT_VALUE_TYPE_PTR), .value_len = (sizeof(ble_hid_info_t)), .value = (uint32_t)(&_hid_info_value), .permission = ((1U << 0) | (1U << 3)), },

    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2803), .value_type = (EX2_ATT_VALUE_TYPE_DATA), .value_len = (1), .value = (uint32_t)(0x04), .permission = ((1U << 0)), },
    { .rsvd = 0, .uuid_len = (EX2_UUID_LEN_2B), .uuid_idx = (0x2A4C), .value_type = (EX2_ATT_VALUE_TYPE_FUNC), .value_len = (1), .value = (uint32_t)(hid_control_point_write), .permission = ((1U << 1) | (1U << 3)), },
# 417 "../main/ex2_profile_hid_mouse.c"
};
