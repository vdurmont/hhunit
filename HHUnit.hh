<?hh

require(__DIR__."/src/autoload.php");

use \HHUnit\Console;
use \HHUnit\ConsoleOptions;

$opts = ConsoleOptions::parse($_SERVER["argv"]);
$console = new Console($opts);
$console->run();
