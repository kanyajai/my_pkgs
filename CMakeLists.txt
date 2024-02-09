cmake_minimum_required(VERSION 3.8)
project(my_pkgs)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(msg_files
  "msg/AddressBook.msg"
  "msg/Num.msg"
  "msg/Sphere.msg"
  )

set(srv_files
  "srv/AddThreeInts.srv"
  )

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
  DEPENDENCIES  geometry_msgs
  )


add_executable(my_node src/my_node.cpp)
ament_target_dependencies(my_node rclcpp std_msgs) # Added line

add_executable(talker src/my_pub.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener src/my_sub.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

add_executable(add2ints_server src/my_add2ints_server.cpp)
ament_target_dependencies(add2ints_server rclcpp example_interfaces)

add_executable(address_books src/my_pub_address_book.cpp)
ament_target_dependencies(address_books rclcpp)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp)
target_link_libraries(address_books "${cpp_typesupport_target}")

target_include_directories(my_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(my_node PUBLIC c_std_99 cxx_std_17)

install(TARGETS 
  my_node 
  talker
  listener
  add2ints_server
  address_books
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(rosidl_default_runtime)
ament_package()