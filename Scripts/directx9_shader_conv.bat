set fxc="C:\Program Files (x86)\Microsoft DirectX SDK (August 2009)\Utilities\bin\x86\fxc.exe"

%fxc% /Fo pixel_shader.bin /Ges -T ps_2_0 -E PS ..\Source\relive_lib\Renderer\DirectX9\pixel_shader.hlsl
python bin2header.py -i pixel_shader.bin -o ..\Source\relive_lib\Renderer\DirectX9\pixel_shader.h -v pixel_shader

%fxc% /Fo cam_fg1_shader.bin /Ges -T ps_2_0 -E PS ..\Source\relive_lib\Renderer\DirectX9\cam_fg1_shader.hlsl
python bin2header.py -i cam_fg1_shader.bin -o ..\Source\relive_lib\Renderer\DirectX9\cam_fg1_shader.h -v cam_fg1_shader

%fxc% /Fo flat_shader.bin /Ges -T ps_2_0 -E PS ..\Source\relive_lib\Renderer\DirectX9\flat_shader.hlsl
python bin2header.py -i flat_shader.bin -o ..\Source\relive_lib\Renderer\DirectX9\flat_shader.h -v flat_shader

%fxc% /Fo flat_shader.bin /Ges -T ps_2_0 -E PS ..\Source\relive_lib\Renderer\DirectX9\gas_shader.hlsl
python bin2header.py -i flat_shader.bin -o ..\Source\relive_lib\Renderer\DirectX9\gas_shader.h -v gas_shader


pause
