<?hh

namespace HHUnit;

use \HHUnit\Core\Config;
use \HHUnit\Runner\Runner;
use \HHUnit\UI\Console;
use \HHUnit\UI\ConsoleOptions;
use \HHUnit\Utils\FileService;

/**
* HHUnit is the main entrypoint of the framework.
* It creates the main services to emulate a dependency injection framework.
* TODO real DI
* Then, it launches the tests.
*/
class HHUnit {
  private static ?HHUnit $instance;
  public Console $console;
  public Config $config;
  public FileService $fileService;
  public Runner $runner;

  public static function getInstance() : HHUnit {
    if (self::$instance == null) {
      self::$instance = new HHUnit();
    }
    return self::$instance;
  }

  public static function run() : void {
    $opts = ConsoleOptions::createFromCommandLine($_SERVER["argv"]);
    self::getInstance()->config->initWithConsoleOptions($opts);

    self::getInstance()->runner->run();

    $console = new Console();
    // TODO ???
    // $runner = new Runner($console);
    // $runner->run();
    $console->run();
  }

  public function __construct() {
    $this->config = new Config();
    $this->console = new Console();
    $this->fileService = new FileService();
    $this->runner = new Runner();
  }
}
