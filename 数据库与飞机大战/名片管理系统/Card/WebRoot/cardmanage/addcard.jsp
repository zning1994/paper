<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ page
	import="java.sql.*,com.manager.dao.*,com.manager.dao.impl.*,com.manager.entity.*,com.manager.util.*"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>


<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
    <base href="<%=basePath%>">
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>增加新名片</title>
<link rel="stylesheet" type="text/css" href="style5.css" />
<link href="css/table.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="js/jquery.js"></script>
<script type="text/javascript" src="cardmanage/users.js"></script>
<!-- <link href="../css/style5.css" rel="stylesheet" type="text/css" /> -->


<script type="text/javascript">
    		$(function(){
				$("#company").change(function(){
        			var sup = document.form1.company.value;
        			$.post("ajaxCompany",{"company":sup},function(response, suatus){
		       			var rs = response.split("-");
		       			var n = document.getElementById("department").length;
		       			document.getElementById("department").length=0;
		       			for(var i=0; i<rs.length; i++){
		       				var op = new Option(rs[i]);
		   					document.getElementById("department").add(op);
		   				}
		       		});
				});
    		});
		</script>
	  <script type="text/javascript">
    		$(function(){
				$("#department").change(function(){
        			var sup = document.form1.company.value;
        			var sup1 = document.form1.department.value;
        			$.post("ajaxDepartment",{"company":sup,"department":sup1},function(response, suatus){
		       			var rs = response.split("-");
		       			var n = document.getElementById("position").length;
		       			document.getElementById("position").length=0;
		       			for(var i=0; i<rs.length; i++){
		       				var op = new Option(rs[i]);
		   					document.getElementById("position").add(op);
		   				}
		       		});
				});
    		});
		</script>

<script>
	function previewImage(file)

	{

		var MAXWIDTH = 260;

		var MAXHEIGHT = 180;

		var div = document.getElementById('preview');

		if (file.files && file.files[0])

		{

			div.innerHTML = '<img id=imghead>';

			var img = document.getElementById('imghead');

			img.onload = function() {

				var rect = clacImgZoomParam(MAXWIDTH, MAXHEIGHT,
						img.offsetWidth, img.offsetHeight);

				img.width = rect.width;

				img.height = rect.height;

				//                 img.style.marginLeft = rect.left+'px';

				img.style.marginTop = rect.top + 'px';

			}

			var reader = new FileReader();

			reader.onload = function(evt) {
				img.src = evt.target.result;
			}

			reader.readAsDataURL(file.files[0]);

		}
		//兼容IE

		else {

			var sFilter = 'filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(sizingMethod=scale,src="';
			file.select();

			var src = document.selection.createRange().text;

			div.innerHTML = '<img id=imghead>';

			var img = document.getElementById('imghead');

			img.filters.item('DXImageTransform.Microsoft.AlphaImageLoader').src = src;

			var rect = clacImgZoomParam(MAXWIDTH, MAXHEIGHT, img.offsetWidth,
					img.offsetHeight);

			status = ('rect:' + rect.top + ',' + rect.left + ',' + rect.width
					+ ',' + rect.height);

			div.innerHTML = "<div id=divhead style='width:"+rect.width+"px;height:"+rect.height+"px;margin-top:"+rect.top+"px;"+sFilter+src+"\"'></div>";

		}

	}
	function previewImage1(file)

	{

		var MAXWIDTH = 260;

		var MAXHEIGHT = 180;

		var div = document.getElementById('preview1');

		if (file.files && file.files[0])

		{

			div.innerHTML = '<img id=imghead1>';

			var img = document.getElementById('imghead1');

			img.onload = function() {

				var rect = clacImgZoomParam(MAXWIDTH, MAXHEIGHT,
						img.offsetWidth, img.offsetHeight);

				img.width = rect.width;

				img.height = rect.height;

				//                 img.style.marginLeft = rect.left+'px';

				img.style.marginTop = rect.top + 'px';

			}

			var reader = new FileReader();

			reader.onload = function(evt) {
				img.src = evt.target.result;
			}

			reader.readAsDataURL(file.files[0]);

		}
		//兼容IE

		else {

			var sFilter = 'filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(sizingMethod=scale,src="';
			file.select();

			var src = document.selection.createRange().text;

			div.innerHTML = '<img id=imghead1>';

			var img = document.getElementById('imghead1');

			img.filters.item('DXImageTransform.Microsoft.AlphaImageLoader').src = src;

			var rect = clacImgZoomParam(MAXWIDTH, MAXHEIGHT, img.offsetWidth,
					img.offsetHeight);

			status = ('rect:' + rect.top + ',' + rect.left + ',' + rect.width
					+ ',' + rect.height);

			div.innerHTML = "<div id=divhead style='width:"+rect.width+"px;height:"+rect.height+"px;margin-top:"+rect.top+"px;"+sFilter+src+"\"'></div>";

		}

	}
	function clacImgZoomParam(maxWidth, maxHeight, width, height) {

		var param = {
			top : 0,
			left : 0,
			width : width,
			height : height
		};

		if (width > maxWidth || height > maxHeight)

		{

			rateWidth = width / maxWidth;
			rateHeight = height / maxHeight;

			if (rateWidth > rateHeight)

			{

				param.width = maxWidth;

				param.height = Math.round(height / rateWidth);

			} else

			{

				param.width = Math.round(width / rateHeight);

				param.height = maxHeight;

			}

		}

		param.left = Math.round((maxWidth - param.width) / 2);

		param.top = Math.round((maxHeight - param.height) / 2);

		return param;

	}
</script>


        <style type="text/css">
<!--
#Layer1 {
	position:absolute;
	width:408px;
	height:402px;
	z-index:1;
	left: 12px;
	top: 58px;
}
#Layer2 {
	position:absolute;
	width:429px;
	height:451px;
	z-index:2;
	left: 487px;
	top: 63px;
}
-->
        </style>
</head>
  
<body>
<%@taglib prefix="s" uri="/struts-tags" %>
<s:fielderror/>
<div class="info-left">
<form id="form1" name="form1" method="post" action="Card/UploadAction.do" enctype="multipart/form-data" onSubmit="return Check()">
  <div id="Layer1">
    <p>上传图片<br />
        <script for="upload" event="onpropertychange">   
//当 id 为 upload 的对象上的属性发生变化时调用此段代码
//设置隐藏图片的地址为上传控件框的值
pic.src=this.value
      </script>
        <script for="pic" event="onload">
//当 id 为 pic 的对象在装载完成时触发此段代码
this.style.display=""    //以行内元素方式显示隐藏的图片
      </script>
        <script for="pic" event="onerror">
//当 id 为 pic 的对象在装载过程中发生错误时触发此段代码
this.style.display="none"   //隐藏图片
alert("所选文件并非图片，请重新选择")
      </script>
      正面：
  <input type="file" name="myFile" id="myFile2" onChange="previewImage(this)">
  <span id="myFile2error"></span>
    </p>
    <table width="313" border="1" class="gridtable">
      <tr>
        <td width="303" height="191"><div id="preview">

									<img id="imghead" width=100 height=100 border=0
										src='' alt='正面图片'>
								</div></td>
      </tr>
    </table>
    背面：
    <input type="file"  name="myFile" id="myFile" onchange="previewImage1(this)"/>
    <span id="myFileerror"></span>
    <br />
    <table width="312" height="181" border="1" class="gridtable">
      <tr>
        <td width="302" height="175"><div id="preview1">

									<img id="imghead1" width=100 height=100 border=0
										src='' alt="反面图片">
								</div></td>
      </tr>
    </table>
  </div>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  <p>&nbsp;</p>
  
  <div id="Layer2">详细信息 <br />
    <table width="294" border="1" class="gridtable">
      <tr>
        <td width="85">姓名： </td>
        <td width="193"><input type="text" name="usernameS2" id="usernameS2"/>
        <span id="usernameS2error"></span>
        </td>
      </tr>
      <tr>
        <td>所在公司：</td>
        <td><select name="select" id="select">
            <option value="默认" selected >公司名称</option>
            <%
                    			Connection conn = DBConnection.getConnection();
								Statement stmt = conn.createStatement();
								ResultSet rs = stmt.executeQuery("select * from Company");
								while (rs.next()) {
							%>
            <option><%=rs.getString(2)%></option>
            <%
								}
							%>
        </select></td>
      </tr>
      <tr>
        <td>所在部门：</td>
        <td><select name="select" id="select2" >
            <option value="默认" >部门</option>
        </select></td>
      </tr>
      <tr>
        <td>职位：</td>
        <td><select  name="select" id="select3" >
            <option value="默认">职务</option>
        </select></td>
      </tr>
      <tr>
        <td>家庭住址：</td>
        <td><input type="text" name="homeaddress2" id="homeaddress2"/>
         <span id="homeaddress2error"></span>
        </td>
      </tr>
      <tr>
        <td>邮编：</td>
        <td><input type="text" name="postcode2" id="postcode2"/>
        <span id="postcode2error"></span>
        </td>
      </tr>
      <tr>
        <td>联系电话：</td>
        <td><input type="text" name="tel2" id="tel2"/>
        <span id="tel2error"></span>
        </td>
      </tr>
      <tr>
        <td>邮箱：</td>
        <td><input type="text" name="mailbox2" id="mailbox2"/>
        <span id="mailbox2error"></span>
        </td>
      </tr>
      <tr>
        <td>备注：</td>
        <td><textarea name="textarea" cols="20" rows="3"></textarea></td>
      </tr>
      <tr>
        <td>查看权限：</td>
        <td><select name="select">
            <option value="1">全部共享</option>
            <option value="2">公司共享</option>
            <option value="3">部门共享</option>
          </select>
        </td>
      </tr>
    </table>
    <p>&nbsp;</p>
    <p>&nbsp;</p>
     <p>
    <input name="submit" type="submit" value="提交" >
  </p>
  </div>
  <br/>
   <br/>
    <br/>
 
  </form>
</body>
</html>
