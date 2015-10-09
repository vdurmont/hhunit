<?hh // strict

namespace HHUnit\UI;

use \HHUnit\HHUnit;
use \HHUnit\Model\TestCase;
use \HHUnit\Model\TestStatus;
use \HHUnit\Model\TestSummary;
use \HHUnit\Model\TestSuite;

/**
* Util methods to print the output.
*/
class UIUtils {
  public function __construct(private IPrinter $printer) {}

  public function printFailure(string $className, string $methodName, \Exception $e) : void {
    $message = $className."#".$methodName.": ".$e->getMessage();
    $this->printer->writelnWithColor($message, "red");
    $this->printer->writeln($e->getTraceAsString());
  }

  public function printError(string $className, string $methodName, \Exception $e) : void {
    $message = $className.": An error occurred in the method ".$methodName."\nMessage: ".$e->getMessage();
    $this->printer->writelnWithColor($message, "red");
    $this->printer->writeln($e->getTraceAsString());
  }

  public function printTestSuiteStart<T>(TestSuite<T> $testSuite) : void {
    $this->printer->writelnWithColor("Running ".$testSuite->getClass()->getName(), "blue");
  }

  public function printTestSuiteEnd<T>(TestSuite<T> $testSuite) : void {
    $str = $testSuite->getClass()->getName().": ";
    $str .= $testSuite->getNumSuccesses()." success, ";
    $str .= $testSuite->getNumFailures()." failures, ";
    $str .= $testSuite->getNumErrors()." errors, ";
    $str .= self::prettyDuration($testSuite->getStartTime(), $testSuite->getEndTime());
    $str .= ".";
    $color = $testSuite->getNumErrors() > 0 || $testSuite->getNumFailures() > 0 ? "red" : "green";
    $this->printer->writelnWithColor($str, $color);
  }

  public function printSummary(TestSummary $summary) : void {
    $this->printSummaryHeader($summary);
    foreach ($summary->getTestSuites() as $testSuite) {
       $this->printTestSuiteSummary($testSuite);
    }
  }

  public function printSummaryHeader(TestSummary $summary) : void {
    $this->printer->writeln("");
    $this->printer->writelnWithColor("####################", "cyan");
    $this->printer->writelnWithColor("## HHUnit summary ##", "cyan");
    $this->printer->writelnWithColor("####################", "cyan");
    $this->printer->writeln("");
    $this->printer->writeln("Test path: ".$summary->getTestPath());
    $this->printer->writeln("Total time: ".self::prettyDuration($summary->getStartTime(), $summary->getEndTime()));
    $this->printer->writeln("");
  }

  public static function prettyDuration(float $start, float $end) : string {
    $duration = intval($end * 1000) - intval($start * 1000);
    if ($duration === 0) {
      return "0ms";
    }

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

  public function printTestSuiteSummary(TestSuite<mixed> $testSuite) : void {
    $this->printStatusLine($testSuite->getStatus(), $testSuite->getClass()->getName(), 0);
    if ($testSuite->getStatus() == TestStatus::FAILURE) {
      foreach($testSuite->getTestCases() as $testCase) {
        $this->printStatusLine($testCase->getStatus(), $testCase->getTestName(), 1);
      }
    }
  }

  private function printStatusLine(TestStatus $status, string $name, int $indentLevel) : void {
    $numPoints = 25; // This is a constant value
    $indent = self::generateRepetition("\t", $indentLevel);
    $this->printer->write($indent."[");
    switch($status) {
      case TestStatus::ERROR: // FALLTHROUGHT
      case TestStatus::LOADING:
      $this->printer->writeWithColor("ERROR", "red");
      $numPoints -= 5;
      break;
      case TestStatus::SKIPPED:
      $this->printer->writeWithColor("SKIP", "yellow");
      $numPoints -= 4;
      break;
      case TestStatus::SUCCESS:
      $this->printer->writeWithColor("OK", "green");
      $numPoints -= 2;
      break;
      case TestStatus::FAILURE:
      $this->printer->writeWithColor("FAIL", "red");
      $numPoints -= 4;
      break;
    }
    $points = self::generateRepetition(".", $numPoints);
    $this->printer->writeln("] ".$points." ".$name);
  }

  private static function generateRepetition(string $pattern, int $num) : string {
    $str = "";
    for ($i = 0; $i < $num; $i++) {
      $str .= $pattern;
    }
    return $str;
  }
}
