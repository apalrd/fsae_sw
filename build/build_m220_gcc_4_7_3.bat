@REM --------------------------------------------------------------------
@REM Batch file to build example sources to demonstrate the sequence of
@REM commands necessary to complete a build. Replace this batch file with
@REM your favourite build mechanism (such as Make or SCons).
@REM --------------------------------------------------------------------

@REM --------------------------------------------------------------------
@REM Setup tools and paths to required tools.
@REM Edit these to match your environment.
@REM --------------------------------------------------------------------

@REM Set the location for the OpenECU installation
SET OPENECU_BASE=c:\openecu\platform\2_3_0_m670-5_x86-32\

@REM Set the compiler location
SET OPENECU_GCC=%OPENECU_BASE%tools\gcc_4_7_3\ppc\bin\

@REM --------------------------------------------------------------------
@REM Prepare the build output directory
@REM Nothing from this point onwards needs to be edited.
@REM --------------------------------------------------------------------

@REM Set the location for the build output files
SET OPENECU_OUT=build_fsae_sw_gcc_4_7_3\

IF NOT EXIST %OPENECU_OUT% MKDIR %OPENECU_OUT%
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

CD %OPENECU_OUT%
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

@REM --------------------------------------------------------------------
@REM Derive additional path information from above.
@REM --------------------------------------------------------------------

@REM Set the location for the Python tool
SET OPENECU_PYTHON=%OPENECU_BASE%tools\python\

@REM Set the location of the CAPI tool
SET OPENECU_CAPI=%OPENECU_BASE%tools\capi\

@REM Set the executable command to run the CAPI tool
SET OPENECU_CAPI_INPUT=%OPENECU_PYTHON%python -E %OPENECU_CAPI%capi.py -i ..\..\interface_specification\fsae_sw.capi

@REM Get the path for this target
for /f %%i in ('%OPENECU_CAPI_INPUT% --target-path') do set TARGET_PATH=%%i
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

@REM Set the location for the compiler options
SET OPENECU_TARGET=%OPENECU_BASE%targets\%TARGET_PATH%

@REM Set the location for the library
SET OPENECU_LIB=%OPENECU_TARGET%mpc5534_lib\

@REM Set the location for the library include files
SET OPENECU_INC=%OPENECU_LIB%include\

@REM Set the location for the Motorola S-record to Intel hex utility
SET OPENECU_S37_TO_HEX=%OPENECU_BASE%tools\gen_hex_from_s37\

@REM Set the location for tool integration files
SET TOOL_INTEGRATION_DIR=%OPENECU_BASE%tool_integration\


@REM --------------------------------------------------------------------
@REM Create the interface code to link the application and library
@REM --------------------------------------------------------------------

%OPENECU_CAPI_INPUT% --output-code fsae_sw_api
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

@REM --------------------------------------------------------------------
@REM Compile the sources
@REM --------------------------------------------------------------------

@REM Obtain the compiler options related to this hardware
for /f "delims=xxx" %%i in ('%OPENECU_CAPI_INPUT% --cfg-flags') do set CFG_FLAGS=%%i
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-gcc %CFG_FLAGS% -DCFG_DONT_USE_DEPRECATED @%OPENECU_TARGET%mk_cc_gcc_4_7_3.opts -I. -I%OPENECU_INC% -o fsae_sw.o     ..\..\src\fsae_sw.c > fsae_sw.lst
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-gcc %CFG_FLAGS% -DCFG_DONT_USE_DEPRECATED @%OPENECU_TARGET%mk_cc_gcc_4_7_3.opts -I. -I%OPENECU_INC% -o gasflows.o     ..\..\src\gasflows.c > gasflows.lst
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-gcc %CFG_FLAGS% -DCFG_DONT_USE_DEPRECATED @%OPENECU_TARGET%mk_cc_gcc_4_7_3.opts -I. -I%OPENECU_INC% -o gasflows_data.o     ..\..\src\gasflows_data.c > gasflows_data.lst
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-gcc %CFG_FLAGS% -DCFG_DONT_USE_DEPRECATED @%OPENECU_TARGET%mk_cc_gcc_4_7_3.opts -I. -I%OPENECU_INC% -o sensors.o     ..\..\src\sensors.c > sensors.lst
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-gcc %CFG_FLAGS% -DCFG_DONT_USE_DEPRECATED @%OPENECU_TARGET%mk_cc_gcc_4_7_3.opts -I. -I%OPENECU_INC% -o sensors_data.o     ..\..\src\sensors_data.c > sensors_data.lst
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-gcc %CFG_FLAGS% -DCFG_DONT_USE_DEPRECATED @%OPENECU_TARGET%mk_cc_gcc_4_7_3.opts -I. -I%OPENECU_INC% -o epm.o     ..\..\src\epm.c > epm.lst
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-gcc %CFG_FLAGS% -DCFG_DONT_USE_DEPRECATED @%OPENECU_TARGET%mk_cc_gcc_4_7_3.opts -I. -I%OPENECU_INC% -o epm_data.o     ..\..\src\epm_data.c > epm_data.lst
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-gcc %CFG_FLAGS% -DCFG_DONT_USE_DEPRECATED @%OPENECU_TARGET%mk_cc_gcc_4_7_3.opts -I. -I%OPENECU_INC% -o fsae_sw_api.o fsae_sw_api.c > fsae_sw_api.lst
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-gcc %CFG_FLAGS% -DCFG_DONT_USE_DEPRECATED @%OPENECU_TARGET%mk_cc_gcc_4_7_3.opts -I. -I%OPENECU_INC% -o spark.o     ..\..\src\spark.c > spark.lst
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-gcc %CFG_FLAGS% -DCFG_DONT_USE_DEPRECATED @%OPENECU_TARGET%mk_cc_gcc_4_7_3.opts -I. -I%OPENECU_INC% -o spark_data.o     ..\..\src\spark_data.c > spark_data.lst
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-gcc %CFG_FLAGS% -DCFG_DONT_USE_DEPRECATED @%OPENECU_TARGET%mk_cc_gcc_4_7_3.opts -I. -I%OPENECU_INC% -o com_idx.o     ..\..\src\com_idx.c > com_idx.lst
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

@REM --------------------------------------------------------------------
@REM Link the objects
@REM --------------------------------------------------------------------

@%OPENECU_PYTHON%python %OPENECU_CAPI%capi.py -i ..\..\interface_specification\fsae_sw.capi --oe-base-path %OPENECU_BASE% --compiler gcc_4_7_3 --output-linker-file link_m220_gcc_4_7_3.ld.tmp
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_GCC%powerpc-eabispe-ld @%OPENECU_TARGET%mk_link_gcc_4_7_3.opts -L%OPENECU_GCC%..\lib\gcc\powerpc-eabispe\4.7.3 -L%OPENECU_GCC%..\powerpc-eabispe\lib -L%OPENECU_LIB% -T link_m220_gcc_4_7_3.ld.tmp -( --no-whole-archive -l:platform_no_vle_diab_5_5_1_0.a -lgcc -lm -lc fsae_sw_api.o fsae_sw.o gasflows.o gasflows_data.o sensors.o sensors_data.o epm.o epm_data.o spark.o spark_data.o com_idx.o -) -Map fsae_sw.map -o fsae_sw.elf > fsae_sw_ld.log
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

@REM --------------------------------------------------------------------
@REM Create final binary image
@REM --------------------------------------------------------------------

@REM -- generate small binary application file
%OPENECU_GCC%powerpc-eabispe-objcopy -v -O binary -j .text_app_isr -j .text_app_excep -j .text_app_header -j .text_app_pfl_i_ram -j .text_app_pfl_e_ram -j .text_app_pfl_p_ram -j .text_app_pem -j .text_app -j .data -j .sdata fsae_sw.elf image_app_fsae_sw_small.bin.tmp
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

@REM -- generate small binary calibration file
%OPENECU_GCC%powerpc-eabispe-objcopy -v -O binary -j .rodata -j .sdata2 -j .cal_sec fsae_sw.elf image_cal_fsae_sw_small.bin.tmp
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

@REM -- combine image files, populate header, and dump as srecord
%OPENECU_CAPI_INPUT% --output-s-rec fsae_sw_image_small.s37 -ca --img-app image_app_fsae_sw_small.bin.tmp --img-cal image_cal_fsae_sw_small.bin.tmp --gcc-map fsae_sw.map
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

@REM Create Intel hex versions of image files
%OPENECU_PYTHON%python -E %OPENECU_S37_TO_HEX%gen_hex_from_s37.py fsae_sw_image_small.s37 fsae_sw_image_small.hex
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

@REM --------------------------------------------------------------------
@REM Create calibration tool files (ASAP2 etc)
@REM --------------------------------------------------------------------

@REM -- generate textual version of ELF output
%OPENECU_GCC%powerpc-eabispe-objdump -W -h -t fsae_sw.elf > fsae_sw.objdump.tmp
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

%OPENECU_CAPI_INPUT% --output-asap2-generic fsae_sw_generic.a2l --output-asap2-vision fsae_sw_vision.a2l --output-asap2-canape fsae_sw_canape.a2l --output-asap2-inca fsae_sw_inca.a2l  --gcc-objfile fsae_sw.objdump.tmp
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

@REM Create system symbols definition file for PiSnoop
copy /y "%TOOL_INTEGRATION_DIR%pisnoop\snoop_os_defs.snx" .\fsae_sw.snx >nul
@IF %ERRORLEVEL% NEQ 0 GOTO EndError

@GOTO End

:EndError

@ECHO "Error: build incomplete."
PAUSE

:End

cd ..
