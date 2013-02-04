<!doctype html>
<!-- paulirish.com/2008/conditional-stylesheets-vs-css-hacks-answer-neither/ss -->
<!--[if lt IE 7]> <html class="no-js ie6 oldie" lang="<?php print $language->language; ?>"> <![endif]-->
<!--[if IE 7]>    <html class="no-js ie7 oldie" lang="<?php print $language->language; ?>"> <![endif]-->
<!--[if IE 8]>    <html class="no-js ie8 oldie" lang="<?php print $language->language; ?>"> <![endif]-->
<!-- Consider adding an manifest.appcache: h5bp.com/d/Offline -->
<!--[if gt IE 8]><!--> <html class="no-js" lang="<?php print $language->language; ?>"> <!--<![endif]-->
<script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>



<head profile="<?php print $grddl_profile; ?>">
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
	<meta
	name="description" content="" /><meta
	name="keywords" content="" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<!-- <link href='http://fonts.googleapis.com/css?family=Fjalla+One' rel='stylesheet' type='text/css'> -->
	<?php print $head; ?>
	<?php if ($is_front) { $head_title = 'Micro News'; } ?>
	<title><?php print $head_title; ?></title>
	<?php print $styles; ?> 
  
	<!--[if lt IE 8]><link rel="stylesheet" href="css/ie.css" type="text/css" media="screen, projection"><![endif]-->

	<!-- end CSS-->
  
<?php print $scripts; ?>

</head>
	
	<body>
			
			<div class="container">

			<div class="span10 heading-row">
			<div class="row">
				<div class="span4 heading">

				<h1>Micro News</h1>

				</div>
			
			</div>

			</div>


	<div class="span10 menu-row">
			<div class="row">

			<div class="span10 menu-block">
				<div class=" ">
					 

				<?php
					$main_menu = block_get_blocks_by_region('main_menu');
					print render($main_menu);
				?>
				  

			</div>
 			</div>
			
			</div>

			</div>

				   <div class="span10 banner-row">

                        <div class="row">

                        <div class="span10 banner">



                        </div>

                        </div>

                </div>



			
<!-- ############################################################ -->
			   
<?php print $page_top; ?>
<?php print $page; ?>
<?php print $page_bottom; ?> 
<!-- ########################################################### -->

</div>			
	</body>	

	</html>