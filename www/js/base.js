var urlpost = "http://50.57.224.47/html/dev/micronews/?q=phonegap/post";
var baseurl= "http://50.57.224.47/html/dev/micronews";
var nextpage = "#home";
var pictureSource;   
var destinationType;
var latitude;
var longitude;
var story;
var mla_id ='all';
var issue = 'all';
var db;
var shortName = 'locDB';
var version = '1.0';
var displayName = 'locDB';
var maxSize = 1553500; 

function onBodyLoad() {
	document.addEventListener("deviceready", onDeviceReady, false);
}

function onDeviceReady() {
  if (!window.openDatabase) {
      alert('Databases are not supported ');
   return;
  } else {
   db = openDatabase(shortName, version, displayName,maxSize);
   db.transaction(function(tx){
   tx.executeSql( 'CREATE TABLE IF NOT EXISTS city_loc_data(latitude DOUBLE NOT NULL ,longitude DOUBLE NOT NULL,mla_id INTEGER PRIMARY KEY)',[],nullHandler,errorHandler); },errorHandler,successCallBack);
  }   


   pictureSource=navigator.camera.PictureSourceType;
   destinationType=navigator.camera.DestinationType;
   navigator.geolocation.getCurrentPosition(onSuccess, onError);
   $.mobile.changePage("#home");
}

function onSuccess(position) {
       latitude = '23.123';//position.coords.latitude ;
       longitude = '11.232';//position.coords.longitude ;
}

function onError(error) {
	alert('code: '    + error.code    + '\n' + 'message: ' + error.message + '\n');
}

function change_current_loc(){
//alert($('#current_loc').val());
updateNews($('#current_loc').val(),issue,1);
}

function updateCat(event,e,m){
 var source=[];
 $('#category').html('Category:' +e);
 $('.cat_icon').css('border-bottom','4px solid #265bc5');
 $(event.target).css('border-bottom','4px solid #ff2121');
 
$.ajax({type: "GET",url: "xml_data/msgs.xml",dataType: "xml",success: function (xml)  {
  $(xml).find("Category").each(function()
	{ 
	   if($(this).attr('id')== m){
	   
	   $(this).find("msg").each(function(){  source.push($(this).text());});
	 $("#jqxcombobox").jqxComboBox({ source: source, selectedIndex: 0, width: '350px', height: '25px', theme: 'summer' });
	 $("#jqxcombobox").jqxComboBox({ autoOpen: true });
	  $('#jqxcombobox').bind('select', function (event) {
                    var args = event.args;
                    var item = $('#jqxcombobox').jqxComboBox('getItem', args.index);
                    story = item.label;
					
                });
	  }
   });
  }    
  });

 
 }
 function getConsti(){
        var cityDropList = document.getElementById("city");
        //var mlaDropList = document.getElementById("mlaOptions");
        var selCity = cityDropList.options[cityDropList.selectedIndex].value;
        var z = selCity;
		var options = "<option value='' selected='selected'>Choose MLA</option>" ;
      
 $.ajax({
		type: "GET",
		url: "location_mapping.xml",
		dataType: "xml",
		success: function(xml) {$("#mlaConsti").css('display','block');
		//alert(z);
		
		$(xml).find("city[code="+z+"] mla_area").each(function()
		
		       
	    {
		
		options += "<option value='"+$(this).attr("code")+"'>"+$(this).attr("name")+"</option>";
			
	  });
	  $("#mlaOptions").html(options);
 }});
    
}

function getWards(){
        var mlaDropList = document.getElementById("mlaOptions");
        var selMla = mlaDropList.options[mlaDropList.selectedIndex].value;
        var w = selMla;
		var options = "<option value='' selected='selected'>Choose Wards</option>" ;
 $.ajax({
		type: "GET",
		url: "location_mapping.xml",
		dataType: "xml",
		success: function(xml) {$("#wards").css('display','block'); 
		$(xml).find("mla_area[code="+w+"] ward_area").each(function()
	  {
	  
		options += "<option value='"+$(this).attr("code")+"'>"+$(this).attr("name")+"</option>";
	  });
	   $("#wardOptions").html(options);
 }});
}	  

var category_code = "";
var prevSelection = "tab1";

$("#navbar ul li").live("click",function(){
	var newSelection = $(this).children("a").attr("data-tab-class");
	$("."+prevSelection).addClass("ui-screen-hidden");
	$("."+newSelection).removeClass("ui-screen-hidden");
	prevSelection = newSelection;
});

function changePage(){
$.mobile.changePage("#home");
}

function uploadNews(){

//uploadPicture();
sendStory();

}

function takePicture() {
        navigator.camera.getPicture(
            function(uri) {alert("test");
			    var img = document.getElementById('camera_image');
				
                img.style.visibility = "visible";
                img.style.display = "block";
                img.src = uri;
                document.getElementById('camera_status').innerHTML = "Success";
				
            },
            function(e) {
                console.log("Error getting picture: " + e);
                document.getElementById('camera_status').innerHTML = "Error getting picture.";
            },
            { quality: 50, destinationType: navigator.camera.DestinationType.FILE_URI});
    };

function selectPicture() {
        navigator.camera.getPicture(
            function(uri) {
                var img = document.getElementById('camera_image');
                img.style.visibility = "visible";
                img.style.display = "block";
                img.src = uri;
                document.getElementById('camera_status').innerHTML = "Success";
            },
            function(e) {
                console.log("Error getting picture: " + e);
                document.getElementById('camera_status').innerHTML = "Error getting picture.";
            },
            { quality: 50, destinationType: navigator.camera.DestinationType.FILE_URI, sourceType: navigator.camera.PictureSourceType.PHOTOLIBRARY});
}

function BrowseFile() {
        navigator.camera.getPicture(
            function(uri) {
                document.getElementById('file_name').innerHTML = uri;
            },
            function(e) {
                console.log("Error getting picture: " + e);
                document.getElementById('camera_status').innerHTML = "Error getting picture.";
            },
            { quality: 50, destinationType: navigator.camera.DestinationType.FILE_URI, sourceType: navigator.camera.PictureSourceType.PHOTOLIBRARY});
}


function uploadPicture() {
	var img = document.getElementById('camera_image');
	var imageURI = img.src;
	if (!imageURI || (img.style.display == "none")) {
		document.getElementById('camera_status').innerHTML = "Take picture or select picture from library first.";
		return;
	}
	
	server = 'http://phpframeworks.techinflo.com/micronews/upload.php';
	if (server) {
		
		
		var options = new FileUploadOptions();
		options.fileKey="file";
		//options.fileName= $("#storytitle").val()+".jpg";
		options.mimeType="image/jpeg";
		options.chunkedMode = false;

		
		var ft = new FileTransfer();
		ft.upload(imageURI, server, function(r) {
			document.getElementById('camera_status').innerHTML = "Upload successful: "+r.bytesSent+" bytes uploaded.";            	
		}, function(error) {
			document.getElementById('camera_status').innerHTML = "Upload failed: Code = "+error.code;            	
		}, options);
	}
}

function show(recordedVideo)
    {

  window.plugins.videoPlayer.play('recordedVideo');
    }


/*Start Video Capture*/

function captureSuccessVideo(uri) {

var recordedVideo = uri[0].fullPath;
alert(recordedVideo);
var vid = document.getElementById('video_holder');
vid.innerHTML = "<p><a href='#' onclick='show("+recordedVideo+")'>Play File</a></p>";
uploadFile(recordedVideo);
alert(vid.innerHTML );
}

function captureErrorVideo(error) {
	var msg = 'An error occurred during capture: ' + error.code;
	navigator.notification.alert(msg, null, 'Uh oh!');
}
function captureVideo() {
	navigator.device.capture.captureVideo(captureSuccessVideo, captureErrorVideo, {limit: 1});
}
function captureSuccessAudio(uri) {
var recordedAudio = uri[0].fullPath;
alert(recordedAudio);
var aud = document.getElementById('audio_holder');
aud.innerHTML = "Testing<audio id='myAud' controls='controls' height='100' width='100'><source src='"+ recordedAudio +"'  ><source src='"+ recordedAudio +"' ><embed height='100' width='100' src='"+recordedAudio +"'></audio>";
alert(aud.innerHTML);
uploadFile(uri[0].fullPath);
alert(aud.innerHTML);
}

function captureErrorAudio(error) {
	var msg = 'An error occurred during capture: ' + error.code;
	navigator.notification.alert(msg, null, 'Uh oh!');
}
function captureAudio() {
       navigator.device.capture.captureAudio(captureSuccessAudio, captureErrorAudio, {limit: 1});
}


function uploadFile() {
	var ft = new FileTransfer(),
	path = $("#fileUpload").val();

	ft.upload(path,
		"http://phpframeworks.techinflo.com/micronews/upload.php",
		function(result) {
			document.getElementById('camera_status').innerHTML = "Video Upload successful: "+r.bytesSent+" bytes uploaded." ;
		},
		function(error) {
			document.getElementById('camera_status').innerHTML = "Video Upload failed: Code = "+error.code;   
		},
		{ fileName: name });   
}

/*END Video Capture*/

function updateNews(mla_id,issue,pageNo){
	var news_url = baseurl+'?q=phonegap/display_view/'+mla_id+'/'+issue;
	$("#latestlist").html("Retrieving News<br/><img src='images/loader1.gif' alt='Loading'/>");
	var jqxhr = $.ajax( news_url )
    .done(function(data) { $("#latestlist").html(data) })
    .fail(function() { alert("error"); })
   
}


function sendStory() {
	
	var element = document.getElementById('geolocation');
    var geo = longitude+latitude;
	var img = document.getElementById('camera_image');
	//story_image = "testimage"; 		field_newsimage : story_image,
	var cat = 'water';//$("#category").html();
	url = baseurl + '?q=phonegap/post';
	alert(story+cat);
	$.post(urlpost, {
		title:	story,
		field_category :cat,
		longitude1:'23.2323',
		latitude1:'324.343'
        
	}, function(data) {
		alert('your story has been uploaded with id: '+ data );
	}).succcess(alert('posted'));	  
	alert('Your Message is being sent. If this message does not change after two minutes, please check your network connectivity.');
	$('#popupPost').popup("close");
}

function addStory()
{
	$.mobile.changePage("#addstory");
}

function isNumeric(input) {
	return (input - 0) == input && input > 0;
}