<?hh // strict

namespace HHUnit\Examples;

use \HHUnit\Core\ClassLoader;

abstract class AbstractExampleTest {
  <<SetUpClass>>
  public static function setUpClass() : void {
    ClassLoader::loadClass(__DIR__."/MyCalculator.hh");
    ClassLoader::loadClass(__DIR__."/BadUsageException.hh");
  }
}
