<?hh // strict

namespace HHUnit\Core;

use \HHUnit\Exception\UnparseableException;
use \HHUnit\Model\LifecycleIdentifier;
use \HHUnit\Model\TestSuite;

class TestSuiteBuilder {
  private ClassParser $classParser;

  public function __construct(IFileService $fileService) {
    $this->classParser = new ClassParser($fileService);
  }

  public function buildTestSuite<T>(string $path) : ?TestSuite<T> {
    try {
      $className = $this->classParser->getClassName($path);
    } catch(UnparseableException $e) {
      return null;
    }
    ClassLoader::loadClass($path);
    $class = new \ReflectionClass($className);

    if ($class->isAbstract() || $class->getAttribute("HHUnit") === null) {
      // Cannot instantiate an abstract class and do not instantiate if it is not annotated with <<HHUnit>>
      return null;
    }

    $instance = $class->newInstance();
    $testSuite = new TestSuite($path, $class, $instance);


    foreach($class->getMethods() as $method) {
      if ($method->isPublic() && !$method->isStatic() && $method->getAttribute("Test") !== null) {
        $testSuite->addTestMethod($method);
      } else if ($method->isPublic() && $method->isStatic() && $method->getAttribute("SetUpClass") !== null) {
        $testSuite->addLifecycleMethod(LifecycleIdentifier::SET_UP_CLASS, $method);
      } else if ($method->isPublic() && $method->isStatic() && $method->getAttribute("TearDownClass") !== null) {
        $testSuite->addLifecycleMethod(LifecycleIdentifier::TEAR_DOWN_CLASS, $method);
      } else if ($method->isPublic() && !$method->isStatic() && $method->getAttribute("SetUp") !== null) {
        $testSuite->addLifecycleMethod(LifecycleIdentifier::SET_UP, $method);
      } else if ($method->isPublic() && !$method->isStatic() && $method->getAttribute("TearDown") !== null) {
        $testSuite->addLifecycleMethod(LifecycleIdentifier::TEAR_DOWN, $method);
      }
    }

    return $testSuite;
  }
}
