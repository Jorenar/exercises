find_library(XDGDIRS XDGdirs REQUIRED)
find_package(Curses REQUIRED)
find_package(SQLite3 REQUIRED)
find_library(readline readline REQUIRED)

add_executable("${PROJECT_NAME}" main.cpp
  db.cpp
  base.cpp
  clients.cpp
  orders.cpp
  util.cpp
)

target_link_libraries("${PROJECT_NAME}"
  ${CURSES_LIBRARIES}
  ${SQLite3_LIBRARIES}
  ${XDGDIRS}
  ${readline}
  BPRINTER
)
