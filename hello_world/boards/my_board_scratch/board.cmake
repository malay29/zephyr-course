if(CONFIG_BOARD_MY_BOARD_SCRATCH_NRF5340_CPUAPP OR CONFIG_BOARD_MY_BOARD_SCRATCH_NRF5340_CPUAPP_NRF7001)
  board_runner_args(nrfutil "--ext-mem-config-file=${BOARD_DIR}/support/nrf7002dk_spi_nrfutil_config.json")
  board_runner_args(jlink "--device=nrf5340_xxaa_app" "--speed=4000")
endif()

include(${ZEPHYR_BASE}/boards/common/nrfutil.board.cmake)
include(${ZEPHYR_BASE}/boards/common/nrfjprog.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
