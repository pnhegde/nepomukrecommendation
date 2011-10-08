set(nepomukrecommendation_SRCS
   nepomukrecommendation.cpp
   main.cpp
   nepomukrecommendationview.cpp
 )

kde4_add_ui_files(nepomukrecommendation_SRCS nepomukrecommendationview_base.ui prefs_base.ui)

kde4_add_kcfg_files(nepomukrecommendation_SRCS settings.kcfgc )

kde4_add_executable(nepomukrecommendation ${nepomukrecommendation_SRCS})

target_link_libraries(nepomukrecommendation
  ${KDE4_KDEUI_LIBS}
  ${KDE4_KIO_LIBS}
  ${NEPOMUK_LIBRARIES}
  ${NEPOMUK_QUERY_LIBRARIES}
  ${SOPRANO_LIBRARIES}
  ${NEPOMUKEXTRAS_INCLUDE_DIR}   )

install(TARGETS nepomukrecommendation ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( PROGRAMS nepomukrecommendation.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES nepomukrecommendation.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES nepomukrecommendationui.rc  DESTINATION  ${DATA_INSTALL_DIR}/nepomukrecommendation )
