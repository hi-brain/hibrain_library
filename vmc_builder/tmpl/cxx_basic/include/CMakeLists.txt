add_subdirectory({{ profile['BasicInfo']['name'] }})

MAP_ADD_STR(hdrs "${PROJECT_NAME}/" headers)
set(headers ${headers} PARENT_SCOPE)
