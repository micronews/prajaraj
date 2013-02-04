<?php

function __autoload($className=null) {
	$classes = array (
        'QConfig.class.php', 
        'QInflector.class.php', 
        'QTool.class.php', 
        'QGoogleGraph.class.php', 
        'QVizualisationGoogleGraph.class.php', 
        'QApikeyGoogleGraph.class.php', 
	);

	foreach($classes as $class) {
		require_once($class);
	}

	require_once($className.".class.php");

}