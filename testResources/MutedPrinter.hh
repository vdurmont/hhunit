<?hh // strict

use \HHUnit\UI\IPrinter;

/**
* Implementation of IPrinter that doesn't print anything :)
* Used to have a clean output when testing the runners.
*/
class MutedPrinter implements IPrinter {
  public function write(string $str) : void {
  }

  public function writeWithColor(string $str, string $color) : void {
  }

  public function writeln(string $str) : void {
  }

  public function writelnWithColor(string $str, string $color) : void {
  }

  public function close(bool $isSuccess) : void {
  }
}
