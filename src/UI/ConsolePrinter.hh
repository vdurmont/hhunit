<?hh // strict

namespace HHUnit\UI;

use \HHUnit\UI\ConsoleColors;
use \HHUnit\UI\IPrinter;

/**
* Manages all the access to the console.
*/
class ConsolePrinter implements IPrinter {
  public function write(string $str) : void {
    echo $str;
  }

  public function writeWithColor(string $str, string $color) : void {
    echo ConsoleColors::color($str, $color, null);
  }

  public function writeln(string $str) : void {
    $this->write($str."\n");
  }

  public function writelnWithColor(string $str, string $color) : void {
    $this->writeWithColor($str."\n", $color);
  }

  public function close(bool $isSuccess) : void {
    $code = $isSuccess ? 0 : 1;
    exit($code);
  }
}
