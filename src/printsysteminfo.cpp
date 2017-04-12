#include <vector>
#include <sstream>
#include "common.hpp"

/** Display OpenGL system info.
 Refer to
  - [glGetString](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetString.xhtml)
  - [glGetIntegerv](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGet.xhtml)

 Output:
@code
vendor: Intel Inc.
renderer: Intel(R) HD Graphics 6000
version: 4.1 INTEL-10.12.13
shading lanuage version: 4.10
extensions:
 0: GL_ARB_blend_func_extended
 1: GL_ARB_draw_buffers_blend
 2: GL_ARB_draw_indirect
 3: GL_ARB_ES2_compatibility
 4: GL_ARB_explicit_attrib_location
 5: GL_ARB_gpu_shader_fp64
 6: GL_ARB_gpu_shader5
 7: GL_ARB_instanced_arrays
 8: GL_ARB_internalformat_query
 9: GL_ARB_occlusion_query2
 10: GL_ARB_sample_shading
 11: GL_ARB_sampler_objects
 12: GL_ARB_separate_shader_objects
 13: GL_ARB_shader_bit_encoding
 14: GL_ARB_shader_subroutine
 15: GL_ARB_shading_language_include
 16: GL_ARB_tessellation_shader
 17: GL_ARB_texture_buffer_object_rgb32
 18: GL_ARB_texture_cube_map_array
 19: GL_ARB_texture_gather
 20: GL_ARB_texture_query_lod
 21: GL_ARB_texture_rgb10_a2ui
 22: GL_ARB_texture_storage
 23: GL_ARB_texture_swizzle
 24: GL_ARB_timer_query
 25: GL_ARB_transform_feedback2
 26: GL_ARB_transform_feedback3
 27: GL_ARB_vertex_attrib_64bit
 28: GL_ARB_vertex_type_2_10_10_10_rev
 29: GL_ARB_viewport_array
 30: GL_EXT_debug_label
 31: GL_EXT_debug_marker
 32: GL_EXT_framebuffer_multisample_blit_scaled
 33: GL_EXT_texture_compression_s3tc
 34: GL_EXT_texture_filter_anisotropic
 35: GL_EXT_texture_sRGB_decode
 36: GL_APPLE_client_storage
 37: GL_APPLE_container_object_shareable
 38: GL_APPLE_flush_render
 39: GL_APPLE_object_purgeable
 40: GL_APPLE_rgb_422
 41: GL_APPLE_row_bytes
 42: GL_APPLE_texture_range
 43: GL_ATI_texture_mirror_once
 44: GL_NV_texture_barrier
 -----
 Max. number of supported vertex attributes: 16
@endcode
*/
int print_system_info()
{
  GLFWwindow *window;
  create_context(&window);

  const GLubyte* vendor = glGetString(GL_VENDOR);
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  const GLubyte* shading_language_version = glGetString(GL_SHADING_LANGUAGE_VERSION);

  std::stringstream ss;
  ss << "vendor: " << (char*)vendor << std::endl
     << "renderer: " << (char*)renderer << std::endl
     << "version: " << (char*)version << std::endl
     << "shading lanuage version: " << (char*)shading_language_version << std::endl
     << "extensions: " << std::endl
     ;

  GLint n=0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &n);
  for (GLint i = 0; i < n; ++i)
  {
    const GLubyte* extension = glGetStringi(GL_EXTENSIONS, (GLuint)i);
    ss << " " << i << ": " << (char*)extension << std::endl;
  }
  ss << "-----" << std::endl;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n);
  ss << "Max. number of supported vertex attributes: " << n << std::endl;
  std::cout << ss.str();

  glfwTerminate();

  return 0;
}
