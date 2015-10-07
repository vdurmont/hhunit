<?hh // strict

use \HHUnit\Assert\Assert;
use \HHUnit\Runner\ClassParser;

class ClassParserTest {
  <<Test>>
  public function getClassNameFromContent_with_a_simple_class() : void {
    $content = self::getContent("class1");
    $className = ClassParser::getClassNameFromContent($content);
    Assert::equals("SimpleClass", $className);
  }

  <<Test>>
  public function getClassNameFromContent_with_a_class_with_namespace() : void {
    $content = self::getContent("class2");
    $className = ClassParser::getClassNameFromContent($content);
    Assert::equals("MyAwesomeNamespace\SubNamespace\ClassWithNamespace", $className);
  }

  <<Test>>
  public function getClassNameFromContent_with_an_invalid_content() : void {
    $content = self::getContent("class3");
    $className = ClassParser::getClassNameFromContent($content);
    Assert::isNull($className);
  }

  private static function getContent(string $name) : string {
    $path = __DIR__."/../../testResources/Runner/ClassParserTest_".$name.".hh";
    return file_get_contents($path);
  }
}
