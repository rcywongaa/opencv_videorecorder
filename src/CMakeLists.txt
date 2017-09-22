set(SRC
    main.cpp
)

find_package(OpenCV REQUIRED)

add_executable(recorder ${SRC})
target_link_libraries(recorder ${OpenCV_LIBS})
