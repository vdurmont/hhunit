<?hh // strict

namespace HHUnit\UI;

use \HHUnit\HHUnit;
use \HHUnit\Model\TestCase;
use \HHUnit\Model\TestStatus;
use \HHUnit\Model\TestSuite;

/**
* Util methods to print the output.
*/
class UIUtils {
  public static function printFailure(string $className, string $methodName, \Exception $e) : void {
    $message = $className."#".$methodName.": ".$e->getMessage();
    HHUnit::getPrinter()->writelnWithColor($message, "red");
    HHUnit::getPrinter()->writeln($e->getTraceAsString());
  }

  public static function printError(string $className, string $methodName, \Exception $e) : void {
    $message = $className.": An error occurred in the method ".$methodName."\nMessage: ".$e->getMessage();
    HHUnit::getPrinter()->writelnWithColor($message, "red");
    HHUnit::getPrinter()->writeln($e->getTraceAsString());
  }

  public static function printTestSuiteStart(TestSuite $testSuite) : void {
    HHUnit::getPrinter()->writelnWithColor("Running ".$testSuite->getClassName(), "blue");
  }

  public static function printTestSuiteEnd(TestSuite $testSuite) : void {
    $str = $testSuite->getClassName().": ";
    $str .= $testSuite->getNumSuccesses()." success, ";
    $str .= $testSuite->getNumFailures()." failures, ";
    $str .= $testSuite->getNumErrors()." errors, ";
    $str .= self::prettyDuration($testSuite->getStartTime(), $testSuite->getEndTime());
    $str .= ".";
    $color = $testSuite->getNumErrors() > 0 || $testSuite->getNumFailures() > 0 ? "red" : "green";
    HHUnit::getPrinter()->writelnWithColor($str, $color);
  }

  public static function printSummaryHeader(string $testPath, float $startTime, float $endTime) : void {
    HHUnit::getPrinter()->writeln("");
    HHUnit::getPrinter()->writelnWithColor("####################", "cyan");
    HHUnit::getPrinter()->writelnWithColor("## HHUnit summary ##", "cyan");
    HHUnit::getPrinter()->writelnWithColor("####################", "cyan");
    HHUnit::getPrinter()->writeln("");
    HHUnit::getPrinter()->writeln("Test path: ".$testPath);
    HHUnit::getPrinter()->writeln("Total time: ".self::prettyDuration($startTime, $endTime));
    HHUnit::getPrinter()->writeln("");
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

  public static function printTestSuiteSummary(TestSuite $testSuite) : void {
    self::printStatusLine($testSuite->getStatus(), $testSuite->getClassName(), 0);
    if ($testSuite->getStatus() == TestStatus::FAILURE) {
      foreach($testSuite->getTestCases() as $testCase) {
        self::printStatusLine($testCase->getStatus(), $testCase->getTestName(), 1);
      }
    }
  }

  private static function printStatusLine(TestStatus $status, string $name, int $indentLevel) : void {
    $numPoints = 25; // This is a constant value
    $indent = self::generateRepetition("\t", $indentLevel);
    HHUnit::getPrinter()->write($indent."[");
    switch($status) {
      case TestStatus::ERROR: // FALLTHROUGHT
      case TestStatus::LOADING:
      HHUnit::getPrinter()->writeWithColor("ERROR", "red");
      $numPoints -= 5;
      break;
      case TestStatus::SKIPPED:
      HHUnit::getPrinter()->writeWithColor("SKIP", "yellow");
      $numPoints -= 4;
      break;
      case TestStatus::SUCCESS:
      HHUnit::getPrinter()->writeWithColor("OK", "green");
      $numPoints -= 2;
      break;
      case TestStatus::FAILURE:
      HHUnit::getPrinter()->writeWithColor("FAIL", "red");
      $numPoints -= 4;
      break;
    }
    $points = self::generateRepetition(".", $numPoints);
    HHUnit::getPrinter()->writeln("] ".$points." ".$name);
  }

  private static function generateRepetition(string $pattern, int $num) : string {
    $str = "";
    for ($i = 0; $i < $num; $i++) {
      $str .= $pattern;
    }
    return $str;
  }
}
