/*
 * cl_utils.h - CL Utilities
 *
 *  Copyright (c) 2016 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Wind Yuan <feng.yuan@intel.com>
 */

#ifndef XCAM_CL_UTILS_H
#define XCAM_CL_UTILS_H

#include "xcam_utils.h"
#include "interface/data_types.h"
#include "ocl/cl_context.h"
#include "ocl/cl_memory.h"
#include "ocl/cl_video_buffer.h"

#define XCAM_CL_IMAGE_ALIGNMENT_X 4

namespace XCam {

bool dump_image (SmartPtr<CLImage> image, const char *file_name);
bool dump_buffer (SmartPtr<VideoBuffer> buffer, char *file_name);

SmartPtr<CLBuffer> convert_to_clbuffer (
    const SmartPtr<CLContext> &context,
    SmartPtr<VideoBuffer> &buf);

SmartPtr<CLImage> convert_to_climage (
    const SmartPtr<CLContext> &context,
    SmartPtr<VideoBuffer> &buf,
    const CLImageDesc &desc,
    uint32_t offset = 0,
    cl_mem_flags flags = CL_MEM_READ_WRITE);

XCamReturn convert_nv12_mem_to_video_buffer (
    void *nv12_mem, uint32_t width, uint32_t height, uint32_t row_pitch, uint32_t offset_uv,
    SmartPtr<VideoBuffer> &buf);

XCamReturn bowl_view_coords_to_image (
    const VideoBufferInfo& info,
    const BowlDataConfig &config,
    float x_pos, float y_pos, float z_pos,
    float &x_trans, float &y_trans);

XCamReturn
generate_topview_map_table (
    const VideoBufferInfo &stitch_info,
    const BowlDataConfig &config,
    std::vector<float> &map_table,
    int width, int height);

XCamReturn
generate_rectifiedview_map_table (
    const VideoBufferInfo &stitch_info,
    const BowlDataConfig &config,
    std::vector<float> &map_table,
    float angle_start, float angle_end,
    int width, int height);

XCamReturn sample_generate_top_view (
    SmartPtr<VideoBuffer> &stitch_buf,
    SmartPtr<VideoBuffer> top_view_buf,
    const BowlDataConfig &config,
    std::vector<float> &map_table, int frame_id);

XCamReturn sample_generate_rectified_view (
    SmartPtr<VideoBuffer> &stitch_buf,
    SmartPtr<VideoBuffer> rectified_view_buf,
    const BowlDataConfig &config,
    float angle_start, float angle_end,
    std::vector<float> &map_table, int frame_id);
}

#endif //XCAM_CL_UTILS_H

