<?hh

spl_autoload_register(function ($className) {
  $basePackage = "HHUnit\\";
  if (substr($className, 0, strlen($basePackage)) === $basePackage) {
    $className = substr($className, strlen($basePackage));
  }
  $classPath = __DIR__."/".str_replace("\\", "/", $className);

  if (is_readable($classPath.".hh")) {
    require_once $classPath.".hh";
  }

  if (is_readable($classPath.".php")) {
    require_once $classPath.".php";
  }
});
