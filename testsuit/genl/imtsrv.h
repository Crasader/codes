#ifndef __IMTSRV_H__
#define __IMTSRV_H__

enum imtsrv_genl_cmds {
    IMTSRV_CMD_UNSPEC,
    IMTSRV_CMD_GET_WIFI_VERSION,
    IMTSRV_CMD_SET_WIFI_VERSION,
    IMTSRV_CMD_GET_WIFI_TYPE,
    IMTSRV_CMD_SET_WIFI_TYPE,
};

enum imtsrv_genl_attrs {
    IMTSRV_ATTR_UNSPEC,

    IMTSRV_ATTR_WIFI_VERSION,
    IMTSRV_ATTR_WIFI_TYPE,

    __IMTSRV_ATTR_LAST,
    IMTSRV_ATTR_MAX = __IMTSRV_ATTR_LAST - 1,
};

#define IMTSRV_GENL_NAME "IMT_SERVICE"

#endif
