# Configure settings and install targets
# FIXME: Copypasted from Ogre and need lots of changes

if (WIN32)
  set(MYGUI_RELEASE_PATH "/Release")
  set(MYGUI_RELWDBG_PATH "/RelWithDebInfo")
  set(MYGUI_MINSIZE_PATH "/MinSizeRel")
  set(MYGUI_DEBUG_PATH "/Debug")
  set(MYGUI_LIB_RELEASE_PATH "/Release")
  set(MYGUI_LIB_RELWDBG_PATH "/RelWithDebInfo")
  set(MYGUI_LIB_MINSIZE_PATH "/MinSizeRel")
  set(MYGUI_LIB_DEBUG_PATH "/Debug")
  set(MYGUI_PLUGIN_PATH "/opt")
elseif (UNIX)
  set(MYGUI_RELEASE_PATH "")
  set(MYGUI_RELWDBG_PATH "")
  set(MYGUI_MINSIZE_PATH "")
  set(MYGUI_DEBUG_PATH "/debug")
  set(MYGUI_LIB_RELEASE_PATH "")
  set(MYGUI_LIB_RELWDBG_PATH "")
  set(MYGUI_LIB_MINSIZE_PATH "")
  set(MYGUI_LIB_DEBUG_PATH "")
  set(MYGUI_PLUGIN_PATH "/MYGUI")
endif ()

# create vcproj.user file for Visual Studio to set debug working directory
function(mygui_create_vcproj_userfile TARGETNAME)
  if (MSVC)
    configure_file(
	  ${MYGUI_TEMPLATES_DIR}/VisualStudioUserFile.vcproj.user.in
	  ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.vcproj.user
	  @ONLY
	)
  endif ()
endfunction(mygui_create_vcproj_userfile)

# install targets according to current build type
function(mygui_install_target TARGETNAME SUFFIX)
  install(TARGETS ${TARGETNAME}
    RUNTIME DESTINATION "bin${MYGUI_RELEASE_PATH}" CONFIGURATIONS Release None ""
    LIBRARY DESTINATION "lib${MYGUI_LIB_RELEASE_PATH}${SUFFIX}" CONFIGURATIONS Release None ""
    ARCHIVE DESTINATION "lib${MYGUI_LIB_RELEASE_PATH}${SUFFIX}" CONFIGURATIONS Release None ""
    FRAMEWORK DESTINATION "bin${MYGUI_RELEASE_PATH}" CONFIGURATIONS Release None ""
  )
  install(TARGETS ${TARGETNAME}
    RUNTIME DESTINATION "bin${MYGUI_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
    LIBRARY DESTINATION "lib${MYGUI_LIB_RELWDBG_PATH}${SUFFIX}" CONFIGURATIONS RelWithDebInfo
    ARCHIVE DESTINATION "lib${MYGUI_LIB_RELWDBG_PATH}${SUFFIX}" CONFIGURATIONS RelWithDebInfo
    FRAMEWORK DESTINATION "bin${MYGUI_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
  )
  install(TARGETS ${TARGETNAME}
    RUNTIME DESTINATION "bin${MYGUI_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
    LIBRARY DESTINATION "lib${MYGUI_LIB_MINSIZE_PATH}${SUFFIX}" CONFIGURATIONS MinSizeRel
    ARCHIVE DESTINATION "lib${MYGUI_LIB_MINSIZE_PATH}${SUFFIX}" CONFIGURATIONS MinSizeRel
    FRAMEWORK DESTINATION "bin${MYGUI_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
  )
  install(TARGETS ${TARGETNAME}
    RUNTIME DESTINATION "bin${MYGUI_DEBUG_PATH}" CONFIGURATIONS Debug
    LIBRARY DESTINATION "lib${MYGUI_LIB_DEBUG_PATH}${SUFFIX}" CONFIGURATIONS Debug
    ARCHIVE DESTINATION "lib${MYGUI_LIB_DEBUG_PATH}${SUFFIX}" CONFIGURATIONS Debug
    FRAMEWORK DESTINATION "bin${MYGUI_DEBUG_PATH}" CONFIGURATIONS Debug
  )
endfunction(mygui_install_target)

# setup common target settings
function(mygui_config_common TARGETNAME)
  set_target_properties(${TARGETNAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${MYGUI_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${MYGUI_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${MYGUI_BINARY_DIR}/bin
  )
  mygui_create_vcproj_userfile(${TARGETNAME})
endfunction(mygui_config_common)

# setup library build
function(mygui_config_lib LIBNAME)
  mygui_config_common(${LIBNAME})
  if (MYGUI_STATIC)
    # add static prefix, if compiling static version
    set_target_properties(${LIBNAME} PROPERTIES OUTPUT_NAME ${LIBNAME}Static)
  else (MYGUI_STATIC)
    if (CMAKE_COMPILER_IS_GNUCXX)
      # add GCC visibility flags to shared library build
      set_target_properties(${LIBNAME} PROPERTIES COMPILE_FLAGS "${MYGUI_GCC_VISIBILITY_FLAGS}")
	endif (CMAKE_COMPILER_IS_GNUCXX)
  endif (MYGUI_STATIC)
  mygui_install_target(${LIBNAME} "")
  
  if (MYGUI_INSTALL_PDB)
    # install debug pdb files
    if (MYGUI_STATIC)
	  install(FILES ${MYGUI_BINARY_DIR}/lib${MYGUI_LIB_DEBUG_PATH}/${LIBNAME}Static_d.pdb
	    DESTINATION lib${MYGUI_LIB_DEBUG_PATH}
		CONFIGURATIONS Debug
	  )
	  install(FILES ${MYGUI_BINARY_DIR}/lib${MYGUI_LIB_RELWDBG_PATH}/${LIBNAME}Static.pdb
	    DESTINATION lib${MYGUI_LIB_RELWDBG_PATH}
		CONFIGURATIONS RelWithDebInfo
	  )
	else ()
	  install(FILES ${MYGUI_BINARY_DIR}/bin${MYGUI_DEBUG_PATH}/${LIBNAME}_d.pdb
	    DESTINATION bin${MYGUI_DEBUG_PATH}
		CONFIGURATIONS Debug
	  )
	  install(FILES ${MYGUI_BINARY_DIR}/bin${MYGUI_RELWDBG_PATH}/${LIBNAME}.pdb
	    DESTINATION bin${MYGUI_RELWDBG_PATH}
		CONFIGURATIONS RelWithDebInfo
	  )
	endif ()
  endif ()
endfunction(mygui_config_lib)

# setup plugin build
function(mygui_config_plugin PLUGINNAME)
  mygui_config_common(${PLUGINNAME})
  if (MYGUI_STATIC)
    # add static prefix, if compiling static version
    set_target_properties(${PLUGINNAME} PROPERTIES OUTPUT_NAME ${PLUGINNAME}Static)
  else (MYGUI_STATIC)
    if (CMAKE_COMPILER_IS_GNUCXX)
      # add GCC visibility flags to shared library build
      set_target_properties(${PLUGINNAME} PROPERTIES COMPILE_FLAGS "${MYGUI_GCC_VISIBILITY_FLAGS}")
      # disable "lib" prefix on Unix
      set_target_properties(${PLUGINNAME} PROPERTIES PREFIX "")
	endif (CMAKE_COMPILER_IS_GNUCXX)	
  endif (MYGUI_STATIC)
  mygui_install_target(${PLUGINNAME} ${MYGUI_PLUGIN_PATH})

  if (MYGUI_INSTALL_PDB)
    # install debug pdb files
    if (MYGUI_STATIC)
	  install(FILES ${MYGUI_BINARY_DIR}/lib${MYGUI_LIB_DEBUG_PATH}/${PLUGINNAME}Static_d.pdb
	    DESTINATION lib${MYGUI_LIB_DEBUG_PATH}/opt
		CONFIGURATIONS Debug
	  )
	  install(FILES ${MYGUI_BINARY_DIR}/lib${MYGUI_LIB_RELWDBG_PATH}/${PLUGINNAME}Static.pdb
	    DESTINATION lib${MYGUI_LIB_RELWDBG_PATH}/opt
		CONFIGURATIONS RelWithDebInfo
	  )
	else ()
	  install(FILES ${MYGUI_BINARY_DIR}/bin${MYGUI_DEBUG_PATH}/${PLUGINNAME}_d.pdb
	    DESTINATION bin${MYGUI_DEBUG_PATH}
		CONFIGURATIONS Debug
	  )
	  install(FILES ${MYGUI_BINARY_DIR}/bin${MYGUI_RELWDBG_PATH}/${PLUGINNAME}.pdb
	    DESTINATION bin${MYGUI_RELWDBG_PATH}
		CONFIGURATIONS RelWithDebInfo
	  )
	endif ()
  endif ()
endfunction(mygui_config_plugin)

# setup Ogre demo build
function(mygui_config_sample SAMPLENAME)
  mygui_config_common(${SAMPLENAME})

  # set install RPATH for Unix systems
  if (UNIX AND MYGUI_FULL_RPATH)
    set_property(TARGET ${SAMPLENAME} APPEND PROPERTY
      INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
    set_property(TARGET ${SAMPLENAME} PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
  endif ()
  
  if (APPLE)
    # On OS X, create .app bundle
    set_property(TARGET ${SAMPLENAME} PROPERTY MACOSX_BUNDLE TRUE)
    # also, symlink frameworks so .app is standalone
    # NOTE: $(CONFIGURATION) is not resolvable at CMake run time, it's only 
    # valid at build time (hence parenthesis rather than braces)
    set (MYGUI_SAMPLE_CONTENTS_PATH 
      ${CMAKE_BINARY_DIR}/bin/$(CONFIGURATION)/${SAMPLENAME}.app/Contents)
    add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
      COMMAND mkdir ARGS -p ${MYGUI_SAMPLE_CONTENTS_PATH}/Frameworks
      COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Ogre.framework 
        ${MYGUI_SAMPLE_CONTENTS_PATH}/Frameworks/
    )
    # now cfg files
    add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
      COMMAND mkdir ARGS -p ${MYGUI_SAMPLE_CONTENTS_PATH}/Resources
      COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/bin/plugins.cfg 
        ${MYGUI_SAMPLE_CONTENTS_PATH}/Resources/
      COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/bin/resources.cfg 
        ${MYGUI_SAMPLE_CONTENTS_PATH}/Resources/
      COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/bin/media.cfg 
        ${MYGUI_SAMPLE_CONTENTS_PATH}/Resources/
      COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/bin/quake3settings.cfg 
        ${MYGUI_SAMPLE_CONTENTS_PATH}/Resources/
    )
    # now plugins
    add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
      COMMAND mkdir ARGS -p ${MYGUI_SAMPLE_CONTENTS_PATH}/Plugins)
    if (MYGUI_BUILD_RENDERSYSTEM_GL)
      add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/RenderSystem_GL.dylib 
          ${MYGUI_SAMPLE_CONTENTS_PATH}/Plugins/
      )
    endif ()
	if (MYGUI_BUILD_PLUGIN_BSP)    
      add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
      COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_BSPSceneManager.dylib 
        ${MYGUI_SAMPLE_CONTENTS_PATH}/Plugins/
      )
    endif()
	if (MYGUI_BUILD_PLUGIN_CG)    
      add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
      COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_CgProgramManager.dylib 
        ${MYGUI_SAMPLE_CONTENTS_PATH}/Plugins/
      )
    endif()
	if (MYGUI_BUILD_PLUGIN_OCTREE)    
      add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
      COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_OctreeSceneManager.dylib 
        ${MYGUI_SAMPLE_CONTENTS_PATH}/Plugins/
      )
    endif()
	if (MYGUI_BUILD_PLUGIN_PCZ)    
      add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
        COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_PCZSceneManager.dylib 
          ${MYGUI_SAMPLE_CONTENTS_PATH}/Plugins/    
      )
      add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
      COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_OctreeZone.dylib 
        ${MYGUI_SAMPLE_CONTENTS_PATH}/Plugins/
      )
    endif()
	if (MYGUI_BUILD_PLUGIN_PFX)    
      add_custom_command(TARGET ${SAMPLENAME} POST_BUILD
      COMMAND ln ARGS -s -f ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/Plugin_ParticleFX.dylib 
        ${MYGUI_SAMPLE_CONTENTS_PATH}/Plugins/
      )
    endif()
  endif (APPLE)

  if (MYGUI_INSTALL_SAMPLES)
    mygui_install_target(${SAMPLENAME} "")
    if (MYGUI_INSTALL_PDB)
      # install debug pdb files
      install(FILES ${MYGUI_BINARY_DIR}/bin${MYGUI_DEBUG_PATH}/${SAMPLENAME}.pdb
        DESTINATION bin${MYGUI_DEBUG_PATH} CONFIGURATIONS Debug
        )
      install(FILES ${MYGUI_BINARY_DIR}/bin${MYGUI_RELWDBG_PATH}/${SAMPLENAME}.pdb
        DESTINATION bin${MYGUI_RELWDBG_PATH} CONFIGURATIONS RelWithDebInfo
        )
    endif ()
  endif ()	

endfunction(mygui_config_sample)

# setup Ogre tool build
function(mygui_config_tool TOOLNAME)
  mygui_config_common(${TOOLNAME})

  # set install RPATH for Unix systems
  if (UNIX AND MYGUI_FULL_RPATH)
    set_property(TARGET ${TOOLNAME} APPEND PROPERTY
      INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
    set_property(TARGET ${TOOLNAME} PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
  endif ()

  if (MYGUI_INSTALL_TOOLS)
    mygui_install_target(${TOOLNAME} "")
    if (MYGUI_INSTALL_PDB)
      # install debug pdb files
      install(FILES ${MYGUI_BINARY_DIR}/bin${MYGUI_DEBUG_PATH}/${TOOLNAME}.pdb
        DESTINATION bin${MYGUI_DEBUG_PATH}
        CONFIGURATIONS Debug
        )
      install(FILES ${MYGUI_BINARY_DIR}/bin${MYGUI_RELWDBG_PATH}/${TOOLNAME}.pdb
        DESTINATION bin${MYGUI_RELWDBG_PATH}
        CONFIGURATIONS RelWithDebInfo
        )
    endif ()
  endif ()	

endfunction(mygui_config_tool)
