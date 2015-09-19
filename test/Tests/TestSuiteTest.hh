<?hh

require_once(__DIR__."/../autoload_tests.hh");

use \HHUnit\Randoms;
use \HHUnit\Test;
use \HHUnit\TestCase;
use \HHUnit\TestSuite;
use \HHUnit\TestStatus;

class TestSuiteTest extends Test {
  public function test_construct() {
    $testCases = array(
      new TestCase(Randoms::randomString(), TestStatus::SKIPPED),
      new TestCase(Randoms::randomString(), TestStatus::SUCCESS),
      new TestCase(Randoms::randomString(), TestStatus::SUCCESS),
      new TestCase(Randoms::randomString(), TestStatus::FAILURE),
      new TestCase(Randoms::randomString(), TestStatus::FAILURE),
      new TestCase(Randoms::randomString(), TestStatus::FAILURE)
    );

    $testSuite = new TestSuite(Randoms::randomString(), TestStatus::FAILURE, $testCases);

    $this->assertEquals(2, $testSuite->getNumSuccess());
    $this->assertEquals(6, $testSuite->getNumTotal());
  }
}
