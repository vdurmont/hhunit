<?hh

use \HHUnit\Test;
use \HHUnit\Parser;

class ParserTest extends Test {
  public function test_SimpleClass() : void {
    $fileContent = <<<EOT
<?hh

class SimpleClass {
}
EOT;
    $className = Parser::parseFileContent($fileContent);
    $this->assertEquals("SimpleClass", $className);
  }

  public function test_ClassWithNameSpace() : void {
    $fileContent = <<<EOT
<?hh

namespace MyAwesomeNamespace;

class ClassWithNamespace {
}
EOT;
    $className = Parser::parseFileContent($fileContent);
    $this->assertEquals("MyAwesomeNamespace\ClassWithNamespace", $className);
  }

  public function test_with_invalid() : void {
    $fileContent = <<<EOT
<?hh

namespace MyAwesomeNamespace;

noclass ClassWithNamespace {
}
EOT;
    $className = Parser::parseFileContent($fileContent);
    $this->assertNull($className);
  }
}
