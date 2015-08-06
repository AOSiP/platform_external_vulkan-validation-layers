/**************************************************************************
 *
 * Copyright 2014 Lunarg, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/

#include <stdio.h>
#include <string>
extern "C" {
#include "glv_common.h"
#include "glv_tracelog.h"
#include "glv_filelike.h"
#include "glv_trace_packet_utils.h"
}
#include "glvreplay_main.h"
#include "glvreplay_factory.h"
#include "glvreplay_seq.h"
#include "glvreplay_window.h"
#include "getopt/getopt.h"

glvreplay_settings replaySettings = { NULL, 1, NULL };

glv_SettingInfo g_settings_info[] =
{
    { "t", "TraceFile", GLV_SETTING_STRING, &replaySettings.pTraceFilePath, &replaySettings.pTraceFilePath, TRUE, "The trace file to replay."},
    { "l", "NumLoops", GLV_SETTING_UINT, &replaySettings.numLoops, &replaySettings.numLoops, TRUE, "The number of times to replay the trace file."},
    { "s", "Screenshot", GLV_SETTING_STRING, &replaySettings.screenshotList, &replaySettings.screenshotList, TRUE, "Comma separated list of frames to take a take snapshots of"},
};

glv_SettingGroup g_replaySettingGroup =
{
    "glvreplay",
    sizeof(g_settings_info) / sizeof(g_settings_info[0]),
    &g_settings_info[0]
};

namespace glv_replay {
int main_loop(Sequencer &seq, glv_trace_packet_replay_library *replayerArray[], unsigned int numLoops)
{
    int err = 0;
    glv_trace_packet_header *packet;
    unsigned int res;
    glv_trace_packet_replay_library *replayer;
    glv_trace_packet_message* msgPacket;
    struct seqBookmark startingPacket;

    // record the location of starting trace packet
    seq.record_bookmark();
    seq.get_bookmark(startingPacket);

    while (numLoops > 0)
    {
        while ((packet = seq.get_next_packet()) != NULL)
        {
            switch (packet->packet_id) {
                case GLV_TPI_MESSAGE:
                    msgPacket = glv_interpret_body_as_trace_packet_message(packet);
                    glv_LogAlways("Packet %lu: Traced Message (%s): %s", packet->global_packet_index, glv_LogLevelToShortString(msgPacket->type), msgPacket->message);
                    break;
                case GLV_TPI_MARKER_CHECKPOINT:
                    break;
                case GLV_TPI_MARKER_API_BOUNDARY:
                    break;
                case GLV_TPI_MARKER_API_GROUP_BEGIN:
                    break;
                case GLV_TPI_MARKER_API_GROUP_END:
                    break;
                case GLV_TPI_MARKER_TERMINATE_PROCESS:
                    break;
                //TODO processing code for all the above cases
                default:
                {
                    if (packet->tracer_id >= GLV_MAX_TRACER_ID_ARRAY_SIZE  || packet->tracer_id == GLV_TID_RESERVED) {
                        glv_LogError("Tracer_id from packet num packet %d invalid.", packet->packet_id);
                        continue;
                    }
                    replayer = replayerArray[packet->tracer_id];
                    if (replayer == NULL) {
                        glv_LogWarning("Tracer_id %d has no valid replayer.", packet->tracer_id);
                        continue;
                    }
                    if (packet->packet_id >= GLV_TPI_BEGIN_API_HERE)
                    {
                        // replay the API packet
                        res = replayer->Replay(replayer->Interpret(packet));
                        if (res != GLV_REPLAY_SUCCESS)
                        {
                           glv_LogError("Failed to replay packet_id %d.",packet->packet_id);
                           return -1;
                        }
                    } else {
                        glv_LogError("Bad packet type id=%d, index=%d.", packet->packet_id, packet->global_packet_index);
                        return -1;
                    }
                }
            }
        }
        numLoops--;
        seq.set_bookmark(startingPacket);
    }
    return err;
}
} // namespace glv_replay

using namespace glv_replay;

void loggingCallback(GlvLogLevel level, const char* pMessage)
{
    switch(level)
    {
    case GLV_LOG_ALWAYS: printf("%s\n", pMessage); break;
    case GLV_LOG_DEBUG: printf("Debug: %s\n", pMessage); break;
    case GLV_LOG_ERROR: printf("Error: %s\n", pMessage); break;
    case GLV_LOG_WARNING: printf("Warning: %s\n", pMessage); break;
    case GLV_LOG_VERBOSE: printf("Verbose: %s\n", pMessage); break;
    default:
        printf("%s\n", pMessage); break;
    }

#if defined(_DEBUG)
#if defined(WIN32)
    OutputDebugString(pMessage);
#endif
#endif
}

extern "C"
int main(int argc, char **argv)
{
    int err = 0;
    glv_SettingGroup* pAllSettings = NULL;
    unsigned int numAllSettings = 0;

    glv_LogSetCallback(loggingCallback);
    glv_LogSetLevel(GLV_LOG_LEVEL_MAXIMUM);

    // apply settings from cmd-line args
    if (glv_SettingGroup_init_from_cmdline(&g_replaySettingGroup, argc, argv, &replaySettings.pTraceFilePath) != 0)
    {
        // invalid options specified
        if (pAllSettings != NULL)
        {
            glv_SettingGroup_Delete_Loaded(&pAllSettings, &numAllSettings);
        }
        return err;
    }

    // merge settings so that new settings will get written into the settings file
    glv_SettingGroup_merge(&g_replaySettingGroup, &pAllSettings, &numAllSettings);

    // Set up environment for screenshot
    if (replaySettings.screenshotList != NULL)
    {
        if (glv_get_global_var(ENV_LAYERS_PATH) == NULL) {
            glv_LogAlways(ENV_LAYERS_PATH "not set in environment, -s option will not work!");
        } else {
            char *evar;

            // Set env var that communicates list to ScreenShot layer
            glv_set_global_var("_VK_SCREENSHOT", replaySettings.screenshotList);

            // Make sure ScreenShot is in layer names
            evar = glv_get_global_var(ENV_LAYER_NAMES);
            if (!evar) {
                glv_set_global_var(ENV_LAYER_NAMES, "ScreenShot");
            } else if (!strstr(evar, "ScreenShot")) {
                // Add ScreenShot to layer names
                char *lnString = GLV_NEW_ARRAY(char, strlen(evar)+strlen(LAYER_NAMES_SEPARATOR "ScreenShot")+1);
                if (lnString) {
                    strcpy(lnString, evar);
                    strcat(lnString, LAYER_NAMES_SEPARATOR "ScreenShot");
                    glv_set_global_var(ENV_LAYER_NAMES, lnString);
                    GLV_DELETE(lnString);
                }
            }
        }
    }
    else
    {
        glv_set_global_var("_VK_SCREENSHOT","");
    }

    // open trace file and read in header
    char* pTraceFile = replaySettings.pTraceFilePath;
    glv_trace_file_header fileHeader;
    FILE *tracefp;

    if (pTraceFile != NULL && strlen(pTraceFile) > 0)
    {
        tracefp = fopen(pTraceFile, "rb");
        if (tracefp == NULL)
        {
            glv_LogError("Cannot open trace file: '%s'.", pTraceFile);
            return 1;
        }
    }
    else
    {
        glv_LogError("No trace file specified.");
        glv_SettingGroup_print(&g_replaySettingGroup);
        if (pAllSettings != NULL)
        {
            glv_SettingGroup_Delete_Loaded(&pAllSettings, &numAllSettings);
        }
        return 1;
    }

    FileLike* traceFile = glv_FileLike_create_file(tracefp);
    if (glv_FileLike_ReadRaw(traceFile, &fileHeader, sizeof(fileHeader)) == false)
    {
        glv_LogError("Unable to read header from file.");
        if (pAllSettings != NULL)
        {
            glv_SettingGroup_Delete_Loaded(&pAllSettings, &numAllSettings);
        }
        GLV_DELETE(traceFile);
        return 1;
    }

    // Make sure trace file version is supported
    if (fileHeader.trace_file_version < GLV_TRACE_FILE_VERSION_MINIMUM_COMPATIBLE)
    {
        glv_LogError("Trace file version %u is older than minimum compatible version (%u).\nYou'll need to make a new trace file, or use an older replayer.", fileHeader.trace_file_version, GLV_TRACE_FILE_VERSION_MINIMUM_COMPATIBLE);
    }

    // load any API specific driver libraries and init replayer objects
    uint8_t tidApi = GLV_TID_RESERVED;
    glv_trace_packet_replay_library* replayer[GLV_MAX_TRACER_ID_ARRAY_SIZE];
    ReplayFactory makeReplayer;
    Display disp(1024, 768, 0, false);

    for (int i = 0; i < GLV_MAX_TRACER_ID_ARRAY_SIZE; i++)
    {
        replayer[i] = NULL;
    }

    for (int i = 0; i < fileHeader.tracer_count; i++)
    {
        uint8_t tracerId = fileHeader.tracer_id_array[i].id;
        tidApi = tracerId;

        const GLV_TRACER_REPLAYER_INFO* pReplayerInfo = &(gs_tracerReplayerInfo[tracerId]);

        if (pReplayerInfo->tracerId != tracerId)
        {
            glv_LogError("Replayer info for TracerId (%d) failed consistency check.", tracerId);
            assert(!"TracerId in GLV_TRACER_REPLAYER_INFO does not match the requested tracerId. The array needs to be corrected.");
        }
        else if (pReplayerInfo->needsReplayer == TRUE)
        {
            // Have our factory create the necessary replayer
            replayer[tracerId] = makeReplayer.Create(tracerId);

            if (replayer[tracerId] == NULL)
            {
                // replayer failed to be created
                if (pAllSettings != NULL)
                {
                    glv_SettingGroup_Delete_Loaded(&pAllSettings, &numAllSettings);
                }
                return err;
            }

            // merge the replayer's settings into the list of all settings so that we can output a comprehensive settings file later on.
            glv_SettingGroup_merge(replayer[tracerId]->GetSettings(), &pAllSettings, &numAllSettings);

            // update the replayer with the loaded settings
            replayer[tracerId]->UpdateFromSettings(pAllSettings, numAllSettings);

            replayer[tracerId]->SetLogCallback(loggingCallback);
            replayer[tracerId]->SetLogLevel(GLV_LOG_LEVEL_MAXIMUM);

            // Initialize the replayer
            err = replayer[tracerId]->Initialize(&disp, &replaySettings);
            if (err) {
                glv_LogError("Couldn't Initialize replayer for TracerId %d.", tracerId);
                if (pAllSettings != NULL)
                {
                    glv_SettingGroup_Delete_Loaded(&pAllSettings, &numAllSettings);
                }
                return err;
            }
        }
    }

    if (tidApi == GLV_TID_RESERVED) {
        glv_LogError("No API specified in tracefile for replaying.");
        if (pAllSettings != NULL)
        {
            glv_SettingGroup_Delete_Loaded(&pAllSettings, &numAllSettings);
        }
        return -1;
    }
 
    // main loop
    Sequencer sequencer(traceFile);
    err = glv_replay::main_loop(sequencer, replayer, replaySettings.numLoops);

    for (int i = 0; i < GLV_MAX_TRACER_ID_ARRAY_SIZE; i++)
    {
        if (replayer[i] != NULL)
        {
            replayer[i]->Deinitialize();
            makeReplayer.Destroy(&replayer[i]);
        }
    }

    if (pAllSettings != NULL)
    {
        glv_SettingGroup_Delete_Loaded(&pAllSettings, &numAllSettings);
    }
    return err;
}