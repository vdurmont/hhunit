<?hh // strict

namespace HHUnit\Runner;

use \HHUnit\HHUnit;
use \HHUnit\Exception\UnparseableException;
use \HHUnit\Model\TestCase;
use \HHUnit\Model\TestStatus;
use \HHUnit\Model\TestSuite;
use \HHUnit\Runner\ClassParser;
use \HHUnit\Runner\TestCaseRunner;
use \HHUnit\Runner\TestSuiteRunner;
use \HHUnit\UI\UIUtils;

class TestRunner {
  public static function run() : void {
    $config = HHUnit::getConfig();

    // Load & run the tests
    $startTime = microtime(true);
    $testPath = $config->getTestPath();
    $testFiles = self::getTestFiles($testPath);
    $setUpPath = $config->getSetUpTestsPath();
    if ($setUpPath !== null) {
      ClassLoader::loadClass($setUpPath);
    }
    $testSuites = self::runTests($testFiles);
    $tearDownPath = $config->getTearDownTestsPath();
    if ($tearDownPath !== null) {
      ClassLoader::loadClass($tearDownPath);
    }
    $endTime = microtime(true);

    // Print the results
    UIUtils::printSummaryHeader($testPath, $startTime, $endTime);

    $isSuccess = true;
    foreach ($testSuites as $testSuite) {
      if ($testSuite->getStatus() !== TestStatus::SUCCESS) {
        $isSuccess = false;
      }
      UIUtils::printTestSuiteSummary($testSuite);
    }
    HHUnit::getPrinter()->writeln("");
    HHUnit::getPrinter()->close($isSuccess);
  }

  private static function getTestFiles(string $testPath) : array<string> {
    $testFiles = array();
    $fs = HHUnit::getFileService();

    if ($fs->isDirectory($testPath) && $testPath != "." && $testPath != "..") {
      $files = $fs->scanDirectory($testPath);
      foreach ($files as $file) {
        if ($file != "." && $file != "..") {
          $testFiles = array_merge($testFiles, self::getTestFiles($testPath."/".$file));
        }
      }
    } else if ($fs->isFile($testPath) && preg_match("/(.+)(Test)\.(hh|php)$/", $testPath) == 1) {
      $testFiles[] = $testPath;
    }

    return $testFiles;
  }

  private static function runTests(array<string> $testFiles) : array<TestSuite> {
    $testSuites = array();

    foreach ($testFiles as $testFile) {
      try {
        $className = ClassParser::getClassName($testFile);
        $testSuite = new TestSuite($testFile, $className);
        TestSuiteRunner::run($testSuite);
        $testSuites[] = $testSuite;
      } catch(UnparseableException $e) {
        HHUnit::getPrinter()->writelnWithColor("Ignoring file at ".$testFile, "yellow");
      }
    }

    return $testSuites;
  }
}
