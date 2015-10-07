# HHUnit

Testing framework for Hack.

_**Disclaimer:** This is a "quick'n'dirty" project that I created while learning Hack and diving into PHP. There are A LOT of things to do before using it in a real production environment :)_

## Table of contents

* [Install and run](#Install-and-run)
* [My first test](#My-first-test)
* [More examples](#More-examples)
* [Configuration](#Configuration)
* [Testing lifecycle](#Testing-lifecycle)
* Extending HHUnit
* Contributing
* License

# Install & run

// TODO

# My first test

Let's say you have a class like this one:

```php
<?hh // strict

class MyCalculator {
  public static function add(int $a, int $b) : int {
    return $a + $b;
  }
}
```

Here is a simple test (the name of the file and the class must end with `Test`):

```php
<?hh // strict

use \HHUnit\Assert\Assert;
use \HHUnit\Runner\ClassLoader;

class MyCalculatorTest {
  <<SetUpClass>>
  public static function setUpClass() : void {
    ClassLoader::loadClass(__DIR__."/MyCalculator.hh");
  }

  <<Test>>
  public function add_with_2_positive_integers() : void {
    $result = MyCalculator::add(3, 4);
    Assert::equals(7, $result);
  }
}
```

Let's run it:

```bash
hhunit /path/to/MyCalculatorTest.hh
```

// TODO screenshot for the output

![Output for MyCalculatorTest.hh](assets/MyCalculatorTestOutput.png)

# More examples

You can find a lot of examples in the [examples](examples) folder. Each subdirectory has a README that will detail the usage.

# Configuration

// TODO

# Testing lifecycle

Here is how HHUnit works:

* **(1)** HHUnit will read the config and require the `setUpTests` file if it is defined.
* **(2)** For each TestSuite:
  * **(2.1)** If your TestSuite has a method with a `<<SetUpClass>>` attribute, it will be executed.
  * **(2.2)** For each TestCase:
    * **(2.2.1)** If your TestSuite has a method with a `<<SetUp>>` attribute, it will be executed.
    * **(2.2.2)** The TestCase method (with a `<<Test>>` attribute) will be executed.
    * **(2.2.3)** If your TestSuite has a method with a `<<TearDown>>` attribute, it will be executed.
  * **(2.3)** If your TestSuite has a method with a `<<TearDownClass>>` attribute, it will be executed.
* **(3)** HHUnit will read the config and require the `tearDownTests` file if it is defined.

// TODO details and examples of what should be used where
