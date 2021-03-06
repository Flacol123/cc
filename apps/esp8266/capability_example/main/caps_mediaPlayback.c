/* ***************************************************************************
 *
 * Copyright 2019-2020 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

#include <string.h>

#include "st_dev.h"
#include "caps_mediaPlayback.h"

#include "freertos/FreeRTOS.h"

static const char **caps_mediaPlayback_get_supportedPlaybackCommands_value(caps_mediaPlayback_data_t *caps_data)
{
    if (!caps_data) {
        printf("caps_data is NULL\n");
        return NULL;
    }
    return (const char **)caps_data->supportedPlaybackCommands_value;
}

static void caps_mediaPlayback_set_supportedPlaybackCommands_value(caps_mediaPlayback_data_t *caps_data, const char **value, int arraySize)
{
    int i;
    if (!caps_data) {
        printf("caps_data is NULL\n");
        return;
    }
    if (caps_data->supportedPlaybackCommands_value) {
        for (i = 0; i < caps_data->supportedPlaybackCommands_arraySize; i++) {
            free(caps_data->supportedPlaybackCommands_value[i]);
        }
        free(caps_data->supportedPlaybackCommands_value);
    }
    caps_data->supportedPlaybackCommands_value = malloc(sizeof(char *) * arraySize);
    if (!caps_data->supportedPlaybackCommands_value) {
        printf("fail to malloc for supportedPlaybackCommands_value\n");
        caps_data->supportedPlaybackCommands_arraySize = 0;
        return;
    }
    for (i = 0; i < arraySize; i++) {
        caps_data->supportedPlaybackCommands_value[i] = strdup(value[i]);
    }

    caps_data->supportedPlaybackCommands_arraySize = arraySize;
}

static void caps_mediaPlayback_attr_supportedPlaybackCommands_send(caps_mediaPlayback_data_t *caps_data)
{
    IOT_EVENT *cap_evt;
    uint8_t evt_num = 1;
    int sequence_no;

    if (!caps_data || !caps_data->handle) {
        printf("fail to get handle\n");
        return;
    }
    if (!caps_data->supportedPlaybackCommands_value) {
        printf("value is NULL\n");
        return;
    }

    cap_evt = st_cap_attr_create_string_array((char *)caps_helper_mediaPlayback.attr_supportedPlaybackCommands.name,
        caps_data->supportedPlaybackCommands_arraySize, caps_data->supportedPlaybackCommands_value, NULL);
    if (!cap_evt) {
        printf("fail to create cap_evt\n");
        return;
    }

    sequence_no = st_cap_attr_send(caps_data->handle, evt_num, &cap_evt);
    if (sequence_no < 0)
        printf("fail to send supportedPlaybackCommands value\n");

    printf("Sequence number return : %d\n", sequence_no);
    st_cap_attr_free(cap_evt);
}


static int caps_mediaPlayback_attr_playbackStatus_str2idx(const char *value)
{
    int index;

    for (index = 0; index < CAP_ENUM_MEDIAPLAYBACK_PLAYBACKSTATUS_VALUE_MAX; index++) {
        if (!strcmp(value, caps_helper_mediaPlayback.attr_playbackStatus.values[index])) {
            return index;
        }
    }   
    return -1; 
}

static const char *caps_mediaPlayback_get_playbackStatus_value(caps_mediaPlayback_data_t *caps_data)
{
    if (!caps_data) {
        printf("caps_data is NULL\n");
        return NULL;
    }
    return caps_data->playbackStatus_value;
}

static void caps_mediaPlayback_set_playbackStatus_value(caps_mediaPlayback_data_t *caps_data, const char *value)
{
    if (!caps_data) {
        printf("caps_data is NULL\n");
        return;
    }
    if (caps_data->playbackStatus_value) {
        free(caps_data->playbackStatus_value);
    }
    caps_data->playbackStatus_value = strdup(value);
}

static void caps_mediaPlayback_attr_playbackStatus_send(caps_mediaPlayback_data_t *caps_data)
{
    IOT_EVENT *cap_evt;
    uint8_t evt_num = 1;
    int sequence_no;

    if (!caps_data || !caps_data->handle) {
        printf("fail to get handle\n");
        return;
    }
    if (!caps_data->playbackStatus_value) {
        printf("value is NULL\n");
        return;
    }

    cap_evt = st_cap_attr_create_string((char *)caps_helper_mediaPlayback.attr_playbackStatus.name,
        caps_data->playbackStatus_value, NULL);
    if (!cap_evt) {
        printf("fail to create cap_evt\n");
        return;
    }

    sequence_no = st_cap_attr_send(caps_data->handle, evt_num, &cap_evt);
    if (sequence_no < 0)
        printf("fail to send playbackStatus value\n");

    printf("Sequence number return : %d\n", sequence_no);
    st_cap_attr_free(cap_evt);
}


static void caps_mediaPlayback_cmd_setPlaybackStatus_cb(IOT_CAP_HANDLE *handle, iot_cap_cmd_data_t *cmd_data, void *usr_data)
{
    caps_mediaPlayback_data_t *caps_data = (caps_mediaPlayback_data_t *)usr_data;
    char *value;
    int index;

    printf("called [%s] func with num_args:%u\n", __func__, cmd_data->num_args);

    index = caps_mediaPlayback_attr_playbackStatus_str2idx(cmd_data->cmd_data[0].string);
    if (index < 0) {
        printf("%s is not supported value for setPlaybackStatus\n", cmd_data->cmd_data[0].string);
        return;
    }
    value = (char *)caps_helper_mediaPlayback.attr_playbackStatus.values[index];

    caps_mediaPlayback_set_playbackStatus_value(caps_data, value);
    if (caps_data && caps_data->cmd_setPlaybackStatus_usr_cb)
        caps_data->cmd_setPlaybackStatus_usr_cb(caps_data);
    caps_mediaPlayback_attr_playbackStatus_send(caps_data);
}

static void caps_mediaPlayback_cmd_play_cb(IOT_CAP_HANDLE *handle, iot_cap_cmd_data_t *cmd_data, void *usr_data)
{
    caps_mediaPlayback_data_t *caps_data = (caps_mediaPlayback_data_t *)usr_data;
    const char* value = caps_helper_mediaPlayback.attr_playbackStatus.values[CAP_ENUM_MEDIAPLAYBACK_PLAYBACKSTATUS_VALUE_PLAYING];

    printf("called [%s] func with num_args:%u\n", __func__, cmd_data->num_args);

    caps_mediaPlayback_set_playbackStatus_value(caps_data, value);
    if (caps_data && caps_data->cmd_play_usr_cb)
        caps_data->cmd_play_usr_cb(caps_data);
    caps_mediaPlayback_attr_playbackStatus_send(caps_data);
}

static void caps_mediaPlayback_cmd_pause_cb(IOT_CAP_HANDLE *handle, iot_cap_cmd_data_t *cmd_data, void *usr_data)
{
    caps_mediaPlayback_data_t *caps_data = (caps_mediaPlayback_data_t *)usr_data;
    const char* value = caps_helper_mediaPlayback.attr_playbackStatus.values[CAP_ENUM_MEDIAPLAYBACK_PLAYBACKSTATUS_VALUE_PAUSED];

    printf("called [%s] func with num_args:%u\n", __func__, cmd_data->num_args);

    caps_mediaPlayback_set_playbackStatus_value(caps_data, value);
    if (caps_data && caps_data->cmd_pause_usr_cb)
        caps_data->cmd_pause_usr_cb(caps_data);
    caps_mediaPlayback_attr_playbackStatus_send(caps_data);
}

static void caps_mediaPlayback_cmd_rewind_cb(IOT_CAP_HANDLE *handle, iot_cap_cmd_data_t *cmd_data, void *usr_data)
{
    caps_mediaPlayback_data_t *caps_data = (caps_mediaPlayback_data_t *)usr_data;
    const char* value = caps_helper_mediaPlayback.attr_playbackStatus.values[CAP_ENUM_MEDIAPLAYBACK_PLAYBACKSTATUS_VALUE_REWINDING];

    printf("called [%s] func with num_args:%u\n", __func__, cmd_data->num_args);

    caps_mediaPlayback_set_playbackStatus_value(caps_data, value);
    if (caps_data && caps_data->cmd_rewind_usr_cb)
        caps_data->cmd_rewind_usr_cb(caps_data);
    caps_mediaPlayback_attr_playbackStatus_send(caps_data);
}

static void caps_mediaPlayback_cmd_fastForward_cb(IOT_CAP_HANDLE *handle, iot_cap_cmd_data_t *cmd_data, void *usr_data)
{
    caps_mediaPlayback_data_t *caps_data = (caps_mediaPlayback_data_t *)usr_data;
    const char* value = caps_helper_mediaPlayback.attr_playbackStatus.values[CAP_ENUM_MEDIAPLAYBACK_PLAYBACKSTATUS_VALUE_FAST_FORWARDING];

    printf("called [%s] func with num_args:%u\n", __func__, cmd_data->num_args);

    caps_mediaPlayback_set_playbackStatus_value(caps_data, value);
    if (caps_data && caps_data->cmd_fastForward_usr_cb)
        caps_data->cmd_fastForward_usr_cb(caps_data);
    caps_mediaPlayback_attr_playbackStatus_send(caps_data);
}

static void caps_mediaPlayback_cmd_stop_cb(IOT_CAP_HANDLE *handle, iot_cap_cmd_data_t *cmd_data, void *usr_data)
{
    caps_mediaPlayback_data_t *caps_data = (caps_mediaPlayback_data_t *)usr_data;
    const char* value = caps_helper_mediaPlayback.attr_playbackStatus.values[CAP_ENUM_MEDIAPLAYBACK_PLAYBACKSTATUS_VALUE_STOPPED];

    printf("called [%s] func with num_args:%u\n", __func__, cmd_data->num_args);

    caps_mediaPlayback_set_playbackStatus_value(caps_data, value);
    if (caps_data && caps_data->cmd_stop_usr_cb)
        caps_data->cmd_stop_usr_cb(caps_data);
    caps_mediaPlayback_attr_playbackStatus_send(caps_data);
}

static void caps_mediaPlayback_init_cb(IOT_CAP_HANDLE *handle, void *usr_data)
{
    caps_mediaPlayback_data_t *caps_data = usr_data;
    if (caps_data && caps_data->init_usr_cb)
        caps_data->init_usr_cb(caps_data);
    caps_mediaPlayback_attr_supportedPlaybackCommands_send(caps_data);
    caps_mediaPlayback_attr_playbackStatus_send(caps_data);
}

caps_mediaPlayback_data_t *caps_mediaPlayback_initialize(IOT_CTX *ctx, const char *component, void *init_usr_cb, void *usr_data)
{
    caps_mediaPlayback_data_t *caps_data = NULL;
    int err;

    caps_data = malloc(sizeof(caps_mediaPlayback_data_t));
    if (!caps_data) {
        printf("fail to malloc for caps_mediaPlayback_data\n");
        return NULL;
    }

    memset(caps_data, 0, sizeof(caps_mediaPlayback_data_t));

    caps_data->init_usr_cb = init_usr_cb;
    caps_data->usr_data = usr_data;

    caps_data->get_supportedPlaybackCommands_value = caps_mediaPlayback_get_supportedPlaybackCommands_value;
    caps_data->set_supportedPlaybackCommands_value = caps_mediaPlayback_set_supportedPlaybackCommands_value;
    caps_data->attr_supportedPlaybackCommands_send = caps_mediaPlayback_attr_supportedPlaybackCommands_send;
    caps_data->get_playbackStatus_value = caps_mediaPlayback_get_playbackStatus_value;
    caps_data->set_playbackStatus_value = caps_mediaPlayback_set_playbackStatus_value;
    caps_data->attr_playbackStatus_str2idx = caps_mediaPlayback_attr_playbackStatus_str2idx;
    caps_data->attr_playbackStatus_send = caps_mediaPlayback_attr_playbackStatus_send;
    if (ctx) {
        caps_data->handle = st_cap_handle_init(ctx, component, caps_helper_mediaPlayback.id, caps_mediaPlayback_init_cb, caps_data);
    }
    if (caps_data->handle) {
        err = st_cap_cmd_set_cb(caps_data->handle, caps_helper_mediaPlayback.cmd_setPlaybackStatus.name, caps_mediaPlayback_cmd_setPlaybackStatus_cb, caps_data);
        if (err) {
            printf("fail to set cmd_cb for setPlaybackStatus of mediaPlayback\n");
    }
        err = st_cap_cmd_set_cb(caps_data->handle, caps_helper_mediaPlayback.cmd_play.name, caps_mediaPlayback_cmd_play_cb, caps_data);
        if (err) {
            printf("fail to set cmd_cb for play of mediaPlayback\n");
    }
        err = st_cap_cmd_set_cb(caps_data->handle, caps_helper_mediaPlayback.cmd_pause.name, caps_mediaPlayback_cmd_pause_cb, caps_data);
        if (err) {
            printf("fail to set cmd_cb for pause of mediaPlayback\n");
    }
        err = st_cap_cmd_set_cb(caps_data->handle, caps_helper_mediaPlayback.cmd_rewind.name, caps_mediaPlayback_cmd_rewind_cb, caps_data);
        if (err) {
            printf("fail to set cmd_cb for rewind of mediaPlayback\n");
    }
        err = st_cap_cmd_set_cb(caps_data->handle, caps_helper_mediaPlayback.cmd_fastForward.name, caps_mediaPlayback_cmd_fastForward_cb, caps_data);
        if (err) {
            printf("fail to set cmd_cb for fastForward of mediaPlayback\n");
    }
        err = st_cap_cmd_set_cb(caps_data->handle, caps_helper_mediaPlayback.cmd_stop.name, caps_mediaPlayback_cmd_stop_cb, caps_data);
        if (err) {
            printf("fail to set cmd_cb for stop of mediaPlayback\n");
    }
    } else {
        printf("fail to init mediaPlayback handle\n");
    }

    return caps_data;
}
