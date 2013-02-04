	<div class="">	
		<div class="span10 content-row">	
	
			<div class="row line-chart">
				<div class="span8 ">

					<h4>Total Updates of Last 10 days</h4>

			<?php

			$visuals = block_get_blocks_by_region('rightsidebar2');
			print render($visuals);

			?>
 				 </div>
			 </div>

			 <br>

			

			<div class="row pie-chart-one">
				<div class="span5 ">


					<h4>Pie Chart Comparison of Issues</h4>

					<?php
				 	$visuals = block_get_blocks_by_region('rightsidebar3');
					print render($visuals);

					?>
				</div>

					<div class="span5">


					<h4>Pie Chart Comparison of Updates</h4>

					<?php
				 	$visuals = block_get_blocks_by_region('rightsidebar1');
					print render($visuals);

					?>
				</div>

			</div>


			 <div class="row line-chart">
				<div class="span8 ">

					<h4>Total Issues Last 10 days</h4>

			<?php

			$visuals = block_get_blocks_by_region('rightsidebar4');
			print render($visuals);

			?>
 				 </div>
			 </div>

		</div>
	</div>