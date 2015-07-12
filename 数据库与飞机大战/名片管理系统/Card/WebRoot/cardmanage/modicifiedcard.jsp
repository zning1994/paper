<%@ page language="java" import="java.util.*,com.manager.entity.*,java.sql.*,com.manager.dao.*,com.manager.dao.impl.*,com.manager.util.*" pageEncoding="utf-8"%>
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
<title>修改名片信息</title>
 <%Card card = (Card)request.getAttribute("card"); 
  	Card_Users cu = (Card_Users)request.getAttribute("card_users");
  	String username = (String) request.getAttribute("username");
  	String companyname = (String) request.getAttribute("companyname");
  	String departmentname = (String) request.getAttribute("departmentname");
  	String position = (String) request.getAttribute("position");
  	String front = (String) request.getAttribute("front");
  	String behind = (String) request.getAttribute("behind");
  
  
  %>
<script type="text/javascript" src="js/jquery.js"></script>
<script type="text/javascript" src="cardmanage/users.js"></script>
<link href="css/style5.css" rel="stylesheet" type="text/css" />
<link href="css/table.css" rel="stylesheet" type="text/css" />


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
	width:412px;
	height:380px;
	z-index:1;
	left: 30px;
	top: 65px;
}
#Layer2 {
	position:absolute;
	width:200px;
	height:115px;
	z-index:2;
	left: 348px;
	top: 155px;
}
#Layer3 {
	position:absolute;
	width:410px;
	height:115px;
	z-index:2;
	left: 521px;
	top: 30px;
}
-->
        </style>
</head>
  
<body>
  <form id="form1" name="form1" method="post" action="Card/CardModifyAction.do" enctype="multipart/form-data" onSubmit="return Check1()">
    <div class="info-left"> 
             
            <div id="Layer3">详细信息 <br />
              <p>&nbsp;</p>
              <input type="hidden" name="cardid" value="<%=cu.getCardId() %>">
              <p>姓名：
                  <input type="text" value="<%=cu.getCardUsersName()%>" name="usernameS"/>
                  <span id="usernameSerror"></span>
              </p>
              <p>所在公司：
                <select name="company" id="company">
                    <option value="默认" selected >公司名称</option>
                    <option value="<%=companyname %>" selected="selected"><%=companyname %></option>
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
                  </select>
              <p>所在部门：
                  <select name="department" id="department" >
                    <option value="<%= departmentname%>" selected="selected"><%= departmentname%></option>
                  </select>
              </p>
              <p>职位：
                  <select  name="position" id="position" >
                    <option value="<%=position%>" selected="selected"><%=position%></option>
                  </select>
              </p>
              <p>家庭住址：
                  <input type="text" value="<%=cu.getAddress() %>" name="homeaddress"/>
                  <span id="homeaddresserror"></span>
              </p>
              <p>邮编：
                  <input type="text" value="<%=cu.getPostCode() %>" name="postcode"/>
                  <span id="postcodeerror"></span>
              </p>
              <p>联系电话：
                  <input type="text" value="<%=cu.getTel() %>" name="tel"/>
                  <span id="telerror"></span>
              </p>
              <p>邮箱：
                  <input type="text" value="<%=cu.getEmail() %>" name="mailbox"/>
                  <span id="mailboxerror"></span>
              </p>
              <p>备注：
                  <textarea rows="3" cols="20" name="remark"><%=card.getNotes() %></textarea>
              </p>
              <p>查看权限：
                <select name="state" id="state">
                    <%if(card.getState()==1){ %>
                    <option value="1" selected>全部共享</option>
                    <option value="2">公司共享</option>
                    <option value="3">部门共享</option>
                    <%} else if(card.getState()==2){ %>
                    <option value="2" selected>公司共享</option>
                    <option value="1">全部共享</option>
                    <option value="3">部门共享</option>
                    <%} else if(card.getState()==3){ %>
                    <option value="3" selected>部门共享</option>
                    <option value="1">全部共享</option>
                    <option value="2">公司共享</option>
                    <%}%>
                  </select>
              <p></p>
                <input type="submit" value="提交"/>
      </div>
            <p>&nbsp;</p>
            <div id="Layer1">
              <p>正面：</p>
              <table width="313" border="1" class="gridtable">
                <tr>
                <div id="preview">
                  <td width="303" height="191"><img id="imghead" src="http://192.168.13.131:8080/temp/<%=front %>" /></td>
                  </div>
                </tr>
                <input type="file" name="myFile" id="myFile" onChange="previewImage(this)" >
                <span id="myFile2error"></span>
              </table>
              <p>反面：</p>
              <table width="312" height="181" border="1" class="gridtable">
                <tr>
                <div id="preview1">
                  <td width="302" height="175"><img src="http://192.168.13.131:8080/temp/<%=behind %>" id="imghead1" /></td>
                </div></tr>
                <input type="file"  name="myFile" id="myFile2" onchange="previewImage1(this)">
                <span id="myFileerror"></span>
              </table>
              <p>&nbsp;</p>
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
            <p>&nbsp;</p>
           
    </div>
   
  </form>
</body>
</html>
