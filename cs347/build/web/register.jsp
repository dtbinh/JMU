<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="stylesheets/tutorstyle.css">
        <link rel="stylesheet" type="text/css" href="stylesheets/bootstrap.css">
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.0.0-alpha1/jquery.js"></script>
        <script type="text/javascript">
            window.setTimeout(function () {
                $("#alert_message").fadeTo(500, 0).slideUp(500, function () {
                    $(this).remove();
                });
            }, 5000);
        </script>
        <title>Tutors@JMU - Register</title>
    </head>
    <body>
        <jsp:include page="header/header.jsp" />
        <s:if test="hasActionErrors()">
            <div class="alert alert-danger" id="alert_message">
                <s:actionerror/>
            </div>
        </s:if>
        <div class="jumbotron">
            <h1 class="col-md-offset-5">Register</h1>
            <hr>
            <form class="form-horizontal col-md-offset-3" action="register" method="post" autocomplete="on">
                <div class="form-group">
                    <label for="inputUserReg" class="col-sm-2 control-label">Username:</label>
                    <div class="col-sm-10">
                        <input type="text" class="form-control" id="inputUserReg" name="inputUserReg" value="<%= userID %>" >
                    </div>
                </div>
                <div class="form-group">
                    <label for="inputEmail" class="col-sm-2 control-label">Email:</label>
                    <div class="col-sm-10">
                        <input type="email" class="form-control" id="inputEmail" name="inputEmail" >
                    </div>
                </div>
                <div class="form-group">
                    <label for="inputFirstName" class="col-sm-2 control-label">First Name:</label>
                    <div class="col-sm-10">
                        <input type="text" class="form-control" id="inputFirstName" name="inputFirstName" >
                    </div>
                </div>
                <div class="form-group">
                    <label for="inputLastName" class="col-sm-2 control-label">Last Name:</label>
                    <div class="col-sm-10">
                        <input type="text" class="form-control" id="inputLastName" name="inputLastName" >
                    </div>
                </div>
                <div class="form-group">
                    <label for="inputPasswordReg" class="col-sm-2 control-label">Password:</label>
                    <div class="col-sm-10">
                        <input type="password" class="form-control" id="inputPasswordReg" name="inputPasswordReg">
                    </div>
                </div>
                <div class="form-group">
                    <label for="inputPasswordConf" class="col-sm-2 control-label">Confirm Password:</label>
                    <div class="col-sm-10">
                        <input type="password" class="form-control" id="inputPasswordConf" name="inputPasswordConf">
                    </div>
                </div>
                <div class="form-group">
                    <p class="tutoring_classes_heading">Please select classes for tutoring. (This is Optional.)</p>
                    <input type="checkbox" name="classes" value="Business">Business
                    <input type="checkbox" name="classes" value="Chemistry">Chemistry
                    <input type="checkbox" name="classes" value="Computer Science">Computer Science
                    <input type="checkbox" name="classes" value="English">English
                    <input type="checkbox" name="classes" value="Health Science">Health Science<br>
                    <input type="checkbox" name="classes" value="Math">Math
                    <input type="checkbox" name="classes" value="Nursing">Nursing
                    <input type="checkbox" name="classes" value="Philosophy">Philosophy
                    <input type="checkbox" name="classes" value="Psychology">Psychology
                    <input type="checkbox" name="classes" value="Science">Science
                </div>
                <br>
                <div class="col-md-offset-1">
                    <fieldset>
                        <legend>Account Type</legend>
                        <label for="student">
                            <input type="radio"
                                   name="radio"
                                   id="student" value="Student" checked="checked" />Student</label>
                        <label for="tutor">
                            <input type="radio"
                                   name="radio"
                                   id="tutor" value="Tutor" />Tutor</label>
                    </fieldset>
                </div>
                <br>
                <div class="form-group">
                    <div class="col-sm-offset-2 col-sm-10">
                        <button type="button" class="btn btn-default" onClick="history.go(-1);
                                return true;">Go Back</button>
                        <button type="submit" class="btn btn-default">Register</button>
                    </div>
                </div>
            </form>
        </div>
        <%@include file="footer/footer.jsp" %> 
    </body>
</html>
