<?hh

namespace HHUnit;

class Summary {
  private string $rootPath;
  private array<TestSuite> $testSuites;
  private float $start;
  private float $end;
  private int $exitCode;

  public function __construct(string $rootPath, array<TestSuite> $testSuites, float $start, float $end) {
    $this->rootPath = $rootPath;
    $this->testSuites = $testSuites;
    $this->start = $start;
    $this->end = $end;
    $this->exitCode = 0;
  }

  public function printSummary() : void {
    echo "\n";
    echo Colors::color("####################\n", "cyan", null);
    echo Colors::color("## HHUnit summary ##\n", "cyan", null);
    echo Colors::color("####################\n", "cyan", null);
    echo "\n";
    echo "Test path: ".$this->rootPath."\n";
    echo "Total time: ".Console::prettyDuration($this->start, $this->end)."\n";
    echo "\n";
    $exitCode = null;
    foreach($this->testSuites as $testSuite) {
      switch($testSuite->getStatus()) {
        case TestStatus::ERROR:
        $exitCode = 1;
        echo "[".Colors::color("ERROR", "red", null)."] ............... ".$testSuite->getClassName()."\n";
        break;
        case TestStatus::SKIPPED:
        $exitCode = 1;
        echo "[".Colors::color("SKIP", "yellow", null)."] ................ ".$testSuite->getClassName()."\n";
        break;
        case TestStatus::SUCCESS:
        if ($exitCode == null) {
          $exitCode = 0;
        }
        echo "[".Colors::color("OK", "green", null)."] .................. ".$testSuite->getClassName()."\n";
        break;
        case TestStatus::FAILURE:
        $exitCode = 1;
        echo "[".Colors::color("FAIL", "red", null)."] ................ ".$testSuite->getClassName()."\n";
        Summary::printCases($testSuite->getTestCases());
        break;
      }
    }
    echo "\n";
    if ($exitCode == null) {
      $exitCode = 1;
    }
    $this->exitCode = $exitCode;
  }

  public function getExitCode() : int {
    return $this->exitCode;
  }

  private static function printCases(array<TestCase> $testCases) {
    foreach($testCases as $testCase) {
      switch($testCase->getStatus()) {
        case TestStatus::ERROR:
        echo "\t[".Colors::color("ERROR", "red", null)."] ............... ".$testCase->getTestName()."\n";
        break;
        case TestStatus::SKIPPED:
        echo "\t[".Colors::color("SKIP", "yellow", null)."] ................ ".$testCase->getTestName()."\n";
        break;
        case TestStatus::SUCCESS:
        echo "\t[".Colors::color("OK", "green", null)."] .................. ".$testCase->getTestName()."\n";
        break;
        case TestStatus::FAILURE:
        echo "\t[".Colors::color("FAIL", "red", null)."] ................ ".$testCase->getTestName()."\n";
        break;
      }
    }
  }
}
