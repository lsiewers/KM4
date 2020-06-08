<?php
    function checkParam($name, $range, $filterType, $debug = true, $exit = true) {
        if (!isset($_GET[$name]) || empty($_GET[$name])) {
            if ($debug) 
                echo "param value $name is empty";
            if ($exit) exit();
        } else if ($_GET[$name] > $range) { 
            if ($debug) 
                echo "param value $name is out of range";
            if ($exit) exit();
        } else if($filterType == false || filter_var($_GET[$name], $filterType)) {
            return $_GET[$name];
        }
    }
?>