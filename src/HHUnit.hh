<?hh // strict

namespace HHUnit;

use \HHUnit\Core\Config;
use \HHUnit\Core\FileService;
use \HHUnit\Core\IConfigLoader;
use \HHUnit\Exception\HHUnitException;
use \HHUnit\Runner\TestRunner;
use \HHUnit\UI\IPrinter;

/**
* HHUnit is the main entrypoint of the test framework.
*/
class HHUnit {
  // TODO real DI with annotations?
  public static ?IPrinter $printer;
  public static ?Config $config;
  public static ?FileService $fileService;

  ////////////////////////////////////
  // MAIN METHODS
  ////////////////////////////////////

  public static function run(IPrinter $printer, IConfigLoader $configLoader) : void {
    // Init the DI components
    self::$printer = $printer;
    self::$config = $configLoader->loadConfig();

    // Run the tests
    TestRunner::run();
  }

  ////////////////////////////////////
  // DI ACCESSORS
  ////////////////////////////////////

  public static function getConfig() : Config {
    if (self::$config == null) {
      throw new HHUnitException("The configuration has not been initialized.");
    }
    return self::$config;
  }

  public static function getFileService() : FileService {
    if (self::$fileService == null) {
      self::$fileService = new FileService();
    }
    return self::$fileService;
  }

  public static function getPrinter() : IPrinter {
    if (self::$printer == null) {
      throw new HHUnitException("The printer has not been initialized.");
    }
    return self::$printer;
  }

  public static function setPrinter(IPrinter $printer) : void {
    self::$printer = $printer;
  }
}
