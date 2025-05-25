add_library(rmlui_backend_common_headers INTERFACE)
target_include_directories(rmlui_backend_common_headers INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
target_sources(rmlui_backend_common_headers INTERFACE
	"${CMAKE_CURRENT_LIST_DIR}/RmlUi_Backend.h"
)

add_library(rmlui_backend_SDL_GL3 INTERFACE)
target_sources(rmlui_backend_SDL_GL3 INTERFACE
	"${CMAKE_CURRENT_LIST_DIR}/RmlUi_Platform_SDL.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RmlUi_Renderer_GL3.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RmlUi_Backend_SDL_GL3.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RmlUi_Platform_SDL.h"
	"${CMAKE_CURRENT_LIST_DIR}/RmlUi_Renderer_GL3.h"
	"${CMAKE_CURRENT_LIST_DIR}/RmlUi_Include_GL3.h"
)
target_link_libraries(rmlui_backend_SDL_GL3 INTERFACE rmlui_backend_common_headers SDL::SDL SDL_image::SDL_image ProjectUtils)
if(UNIX)
	# The OpenGL 3 renderer implementation uses dlopen/dlclose
	# This is required in some UNIX and UNIX-like operating systems to load shared object files at runtime
	target_link_libraries(rmlui_backend_SDL_GL3 INTERFACE ${CMAKE_DL_LIBS})
endif()
if(EMSCRIPTEN)
	# Only Emscripten requires linking to OpenGL::GL, for other platforms we use 'glad' as an OpenGL loader.
	target_link_libraries(rmlui_backend_SDL_GL3 INTERFACE OpenGL::GL)
endif()