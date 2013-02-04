<?php


function micronews_preprocess_page(&$vars){

	if((arg(0) == 'taxonomy') && (arg(1) == 'term')) {

		$term_parents = taxonomy_get_parents(arg(2));
		$term = taxonomy_term_load(arg(2));
		$vname  = $term->vocabulary_machine_name;

		if(($vname == 'constituency') && (!$term_parents)){

		$vars['taxonomy_term_id'] = arg(2);
		$vars['theme_hook_suggestions'][] = 'page__mp';

	}

	if(($vname == 'constituency') && ($term_parents)){

		$vars['taxonomy_term_id'] = arg(2);
		$vars['theme_hook_suggestions'][] = 'page__mla';

	}

  }

	if((arg(0) == 'visual_analytics')){

		
		$vars['theme_hook_suggestions'][] = 'page__analytics';

	}


drupal_add_js(drupal_get_path('theme', 'micronews') . "/js/jquery.mousewheel-3.0.6.pack.js", array("preprocess" => True));
drupal_add_js(drupal_get_path('theme', 'micronews') . "/js/jquery.fancybox.pack.js", array("preprocess" => True));
drupal_add_js(drupal_get_path('theme', 'micronews') . "/js/jquery.fancybox.js", array("preprocess" => True));
drupal_add_js(drupal_get_path('theme', 'micronews') . "/js/custom.js", array("preprocess" => True));


  // if(arg(3) == 'add' && arg(4) == 'microcomments'){
  // 		//$vars['theme_hook_suggestions'][] = 'page__microcomment';
  // }

} 
