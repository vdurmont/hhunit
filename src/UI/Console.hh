<?hh

namespace HHUnit\UI;

use \HHUnit\HHUnit;
use \HHUnit\Runner\TestSuiteRunner;
use \HHUnit\Summary;

class Console {
  public function run() : void {

    // TODO ???
    // $config = $configResolver->resolveConfig($this->options);
    // $testFiles = $fileResolver->getTestFiles($this->config);
    // $summary = $runner->runTests($this->config, $testFiles);


    $realTestPath = Console::getRealTestPath(HHunit::getInstance()->config->getTestPath());
    $files = Console::getTestFiles($realTestPath);

    $testSuites = array();
    $startTime = microtime(true);
    foreach($files as $file) {
      $testSuite = TestSuiteRunner::run($file);
      if ($testSuite != null) {
        $testSuites[] = $testSuite;
      }
    }
    $endTime = microtime(true);

    $summary = new Summary($realTestPath, $testSuites, $startTime, $endTime);
    $summary->printSummary();
    exit($summary->getExitCode());
  }

  public static function fail(string $message) {
    echo $message."\n";
    exit(1);
  }

  private static function getRealTestPath(string $testPath) : string {
    $realPath = realpath($testPath);
    if (!file_exists($realPath)) {
      Console::fail(Colors::color("The testPath doesn't exist: ".$testPath, "red", null));
    }
    return $realPath;
  }

  private static function getTestFiles(string $testPath) {
    $testFiles = array();
    if (is_dir($testPath) && $testPath != "." && $testPath != "..") {
      $files = scandir($testPath);
      foreach ($files as $file) {
        if ($file != "." && $file != "..") {
          $testFiles = array_merge($testFiles, Console::getTestFiles($testPath."/".$file));
        }
      }
    } else if (is_file($testPath) && preg_match("/(.+)(Test)\.(hh|php)$/", $testPath) == 1) {
      $testFiles[] = $testPath;
    }
    return $testFiles;
  }

  public static function prettyDuration(float $start, float $end) : string {
    $duration = intval($end * 1000) - intval($start * 1000);
    $str = "";

    $numMinutes = intval($duration / (1000 * 60));
    if ($numMinutes > 0) {
      $str .= $numMinutes."mn";
    }
    $duration -= ($numMinutes * 1000 * 60);

    $numSeconds = intval($duration / 1000);
    if ($numSeconds > 0) {
      $str .= $numSeconds."s";
    }
    $duration -= ($numSeconds * 1000);

    if ($duration > 0) {
      $str .= $duration."ms";
    }

    return $str;
  }
}
