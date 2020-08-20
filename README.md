# CFU_Project

В проекте я использую библиотеки:<br/>
[SFML-2.5.1](https://www.sfml-dev.org/download.php) - для работы с графикой и музыкой;<br/>
[json](https://github.com/nlohmann/json) - для работы с файлами формата json;<br/>
Winsock2 - для работы с сетью (по умолчанию в Windows);<br/>
fstream - для чтения и записи в файл (стандартная библиотека C++).<br/>

[Инструкция](https://kychka-pc.ru/sfml/urok-1-podklyuchenie-biblioteki-k-srede-razrabotki-visual-studio-2013.html) по установке и подключению библиотеки SFML-2.5.1. <br/>

Для подключения библиотек небходимо ввести данные в настройки проекта:

**C/C++**<br/>
&nbsp;&nbsp;&nbsp; *Общие:*<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Дополнительные каталоги включения: <br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;***C:\Egor\Programming\CFU_Project\libs;C:\Egor\Programming\CFU_Project\libs\SFML-2.5.1\include;%(AdditionalIncludeDirectories)***<br/>
&nbsp;&nbsp;&nbsp; *Препроцессор:*<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Определения препроцессора:<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;***SFML_DYNAMIC;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)***<br/><br/>
**Компоновщик**<br/>
&nbsp;&nbsp;&nbsp; *Общие:*<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Дополнительные каталоги библиотек: <br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;***C:\Egor\Programming\CFU_Project\libs\SFML-2.5.1\lib***<br/>
&nbsp;&nbsp;&nbsp; *Ввод:*<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Дополнительные зависимости: <br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;***sfml-network-d.lib;sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-audio-d.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)***<br/>