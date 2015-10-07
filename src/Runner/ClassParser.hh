<?hh // strict

namespace HHUnit\Runner;

use \HHUnit\HHUnit;
use \HHUnit\Exception\UnparseableException;

class ClassParser {
  public static function getClassName(string $filePath) : string {
    // TODO optimize this. We shouldn't read the entire file
    $fs = HHUnit::getFileService();
    $fileContent = $fs->getFileContent($filePath);
    $className = self::getClassNameFromContent($fileContent);
    if ($className === null) {
      throw new UnparseableException("Cannot find a classname for file at ".$filePath);
    }
    return $className;
  }

  public static function getClassNameFromContent(string $fileContent) : ?string {
    $className = null;
    $namespace = null;

    $matches = array();
    preg_match_all("/(\w+|;|\\\\)/", $fileContent, $matches);

    $tokens = $matches[1];
    $len = count($tokens);
    $i = 0;
    $inClass = false;
    $inNamespace = false;
    while($i < $len && $className == null) {
      $token = $tokens[$i];
      switch($token) {
        case "class":
        $inClass = true;
        break;

        case "namespace":
        $inNamespace = true;
        break;

        case ";":
        if ($inNamespace) {
          $inNamespace = false;
        }
        break;

        default:
        if ($inClass) {
          $className = $token;
        }
        if ($inNamespace) {
          if ($namespace === null) {
            $namespace = "";
          }
          $namespace .= $token;
        }
      }

      $i++;
    }

    if ($className !== null) {
      if ($namespace !== null) {
        $className = $namespace."\\".$className;
      }
      return $className;
    }

    return null;
  }
}
