<?hh // strict

namespace HHUnit\Examples;

use \HHUnit\Core\ClassLoader;

// TODO rename when we handle the files/classes ending in "Test" which are not tests...
abstract class ExampleTestAbstract {
  <<SetUpClass>>
  public static function setUpClass() : void {
    ClassLoader::loadClass(__DIR__."/MyCalculator.hh");
    ClassLoader::loadClass(__DIR__."/BadUsageException.hh");
  }
}
