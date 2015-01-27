#-----------------------------
# Copy of files
#-----------------------------

MACRO(COPY_FILE in_file out_file target)
    ADD_CUSTOM_COMMAND (
    	TARGET     ${target}
    	POST_BUILD
    	COMMAND    ${CMAKE_COMMAND}
    	ARGS       -E copy ${in_file} ${out_file}
    )
ENDMACRO(COPY_FILE)
