qt_add_executable(WordChecker
    main.cxx window.cxx
)
target_link_libraries(WordChecker PRIVATE Qt6::Widgets)

