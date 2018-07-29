<?php
    
    session_start();

    require_once("../login/isLogged.php");

    require_once("../../common/head.php"); 
?>

    <!-- NAVBAR -->
    <div class="navbar-fixed">
    <nav><div class="nav-wrapper">
      <div class="row">
            <a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
            <a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
            <ul id="nav-mobile" class="right hide-on-med-and-down">
                <li><a class="btn-floating btn-medium pulse indigo lighten-1" href="../../index.php"><i class="material-icons">stay_primary_portrait</i></a></li>
                <li><a class="btn-floating btn-medium pulse blue lighten-1" href="../../home.php"><i class="material-icons">home</i></a></li>
                <?php
                    echo "<li><a class='dropdown-trigger btn nav-button' href='../../bugs/index.php'";
                    if($_SESSION['permissions'] == "user")
                        echo " disabled ";
                    echo '><i class="material-icons right">bug_report</i>Bugs</a></li>';
                ?>
                <li><a class='dropdown-trigger btn nav-button' href='../login/logout.php'>Log Out</a></li>
            </ul>
        </div>
    </div></nav>
    </div>
    <!-- NAVBAR MOBILE -->
    <?php require_once("../../common/sidenav-b.php"); ?>
        <li><a href="../../index.php"><i class="material-icons">stay_primary_portrait</i>Start</a></li>
        <li><a class='nav' href='../../home.php'><i class="material-icons">home</i>Home</a></li>
        <?php
            echo '<li><a href="../../bugs/index.php"';
            if($_SESSION['permissions'] == "user")
                echo " class='disabled' ";
            echo '><i class="material-icons">bug_report</i>Bugs</a></li>';
        ?>
        <li><a href="../login/logout.php"><i class="material-icons">exit_to_app</i>Log Out</a></li>
    <?php require_once("../../common/sidenav-e.php"); ?>
    <!-- END OF NAVBAR -->
    
    <div class="container center">

    	<div class="row center">
    		<div class="s12">
    			<h2>About</h2>
    		</div>
    		<div class="s12">
    			<h4 class="modcon">Remember to always be sure about changes you want to update. Once set right username shouldn't be changed very often. You always have to check recapcha button and input your password. Only during changing your email you will have to confirm activation link that will be send by website. While uploading new avatar check if image size is less than 1 MB and its resolution is less than 150x150. Also, keep in mind that website allows you to uploud only JPG type format.</h4>
    		</div>
    	</div>
        
        <div class="row center">
        <!-- Change Username -->
        <div class="center col s12 m6 section scrollspy">
            <a id="changeUsername" class="anchor"></a>
            <h2>Change&nbsp;Username</h2>
            <form action="changeUsername.php" method="post">
                <div class="row"><div class="input-field col s12 m10">
                  <input id="username" type="text" class="validate" name="username" value="<?php
                  if(isset($_SESSION['rem_username']))
                  {
                    echo $_SESSION['rem_username'];
                    unset($_SESSION['rem_username']);
                  }?>">
                  <label for="username"><h5 class="modcon2">New Username</h5></label>
                </div></div>
                
                <div class="row"><div class="input-field col s12 m10">
                  <input id="passwordUsername" type="password" class="validate" name="password" value="<?php
                  if(isset($_SESSION['rem_passwordUsername']))
                  {
                    echo $_SESSION['rem_passwordUsername'];
                    unset($_SESSION['rem_passwordUsername']);
                  }?>">
                  <label for="passwordUsername"><h5 class="modcon2">Password</h5></label>
                </div></div>
                
                <div class="row"><div class="col s12 m10" style="margin-bottom: 10px;">
                    <div class="g-recaptcha" data-sitekey="6Lcs3GIUAAAAAPOX9QzHOA_farHU1IKYvWrWpB-Z"></div>
            	</div></div>

                <div class="row"><div class="col s12">
                <button class="btn waves-effect waves-light nav-button" type="submit" name="action">Update<i class="material-icons right">send</i></button></div></div>
            </form>
            <?php
                if(isset($_SESSION['errorUsername']))
                {
                	echo '<h5 class="errorColor">';
                    echo $_SESSION['errorUsername'];
                    unset($_SESSION['errorUsername']);
                    echo '</h5>';
                }
                else if(isset($_SESSION['successUsername']))
                {
                	echo '<h5 class="successColor">';
                    echo $_SESSION['successUsername'];
                    unset($_SESSION['successUsername']);
                    echo '</h5>';
                }
            ?>
        </div>
        <!-- Change Email -->
        <div class="center col s12 m6 section scrollspy">
            <a id="changeEmail" class="anchor"></a>
            <h2>Change&nbsp;Email</h2>
            <form action="changeEmail.php" method="post">
                <div class="row"><div class="input-field col s12 m10 push-m2">
                  <input id="email" type="text" class="validate" name="email" value="<?php
                  if(isset($_SESSION['rem_email']))
                  {
                    echo $_SESSION['rem_email'];
                    unset($_SESSION['rem_email']);
                  }?>">
                  <label for="email"><h5 class="modcon2">New Email</h5></label>
                </div></div>
                
                <div class="row"><div class="input-field col s12 m10 push-m2">
                  <input id="passwordEmail" type="password" class="validate" name="password" value="<?php
                  if(isset($_SESSION['rem_passwordEmail']))
                  {
                    echo $_SESSION['rem_passwordEmail'];
                    unset($_SESSION['rem_passwordEmail']);
                  }?>">
                  <label for="passwordEmail"><h5 class="modcon2">Password</h5></label>
                </div></div>
                
                <div class="row"><div class="col s12 m10 push-m2" style="margin-bottom: 10px;">
                    <div class="g-recaptcha" data-sitekey="6Lcs3GIUAAAAAPOX9QzHOA_farHU1IKYvWrWpB-Z"></div>
            	</div></div>

                <div class="row"><div class="col s12">
                <button class="btn waves-effect waves-light nav-button" type="submit" name="action">Update<i class="material-icons right">send</i></button></div></div>
            </form>
            <?php
                if(isset($_SESSION['errorEmail']))
                {
                	echo '<h5 class="errorColor">';
                    echo $_SESSION['errorEmail'];
                    unset($_SESSION['errorEmail']);
                    echo '</h5>';
                }
                else if(isset($_SESSION['successEmail']))
                {
                	echo '<h5 class="successColor">';
                    echo $_SESSION['successEmail'];
                    unset($_SESSION['successEmail']);
                    echo '</h5>';
                }
            ?>
        </div>
        </div>




        <div class="row center">
         <!-- Change Password -->
        <div class="center col s12 m6 section scrollspy">
            <a id="changePassword" class="anchor"></a>
              <h2>Change&nbsp;Password</h2>
            <form action="changePassword.php" method="post">
                <div class="row"><div class="input-field col s12 m10">
                  <input id="oldpassword" type="password" class="validate" name="oldpassword" value="<?php
                  if(isset($_SESSION['rem_oldpassword']))
                  {
                    echo $_SESSION['rem_oldpassword'];
                    unset($_SESSION['rem_oldpassword']);
                  }?>">
                  <label for="oldpassword"><h5 class="modcon2">Old Password</h5></label>
                </div></div>

                <div class="row"><div class="input-field col s12 m10">
                  <input id="password" type="password" class="validate" name="password" value="<?php
                  if(isset($_SESSION['rem_password']))
                  {
                    echo $_SESSION['rem_password'];
                    unset($_SESSION['rem_password']);
                  }?>">
                  <label for="password"><h5 class="modcon2">New Password</h5></label>
                </div></div>

                <div class="row"><div class="input-field col s12 m10">
                  <input id="passwordcon" type="password" class="validate" name="passwordcon" value="<?php
                  if(isset($_SESSION['rem_passwordcon']))
                  {
                    echo $_SESSION['rem_passwordcon'];
                    unset($_SESSION['rem_passwordcon']);
                  }?>">
                  <label for="passwordcon"><h5 class="modcon2">Confirm New Password</h5></label>
                </div></div>
                
                <div class="row"><div class="col s12 m10" style="margin-bottom: 10px;">
                    <div class="g-recaptcha" data-sitekey="6Lcs3GIUAAAAAPOX9QzHOA_farHU1IKYvWrWpB-Z"></div>
            	</div></div>

                <div class="row"><div class="col s12">
                <button class="btn waves-effect waves-light nav-button" type="submit" name="action">Update<i class="material-icons right">send</i></button></div></div>
            </form>
            <?php
                if(isset($_SESSION['errorPassword']))
                {
                	echo '<h5 class="errorColor">';
                    echo $_SESSION['errorPassword'];
                    unset($_SESSION['errorPassword']);
                    echo '</h5>';
                }
                else if(isset($_SESSION['successPassword']))
                {
                	echo '<h5 class="successColor">';
                    echo $_SESSION['successPassword'];
                    unset($_SESSION['successPassword']);
                    echo '</h5>';
                }
            ?>
        </div>
        
        <div class="row center">
         <!-- Change Avatar -->
        <div class="center col s12 m6 section scrollspy">
            <a id="changePassword" class="anchor"></a>
              <h2>Change&nbsp;Avatar</h2>
            <form action="changeAvatar.php" method="post" enctype="multipart/form-data">
                
                <div class="file-field input-field col s12 m10 push-m2">
                  <div class="btn"><span>Upload File</span><input type="file" name="file"></div>
                  <div class="file-path-wrapper"><input class="file-path validate" type="text"></div>
                </div>
                
                <div class="row"><div class="input-field col s12 m10 push-m2">
                  <input id="passwordAvatar" type="password" class="validate" name="password" value="<?php
                  if(isset($_SESSION['rem_passwordAvatar']))
                  {
                    echo $_SESSION['rem_passwordAvatar'];
                    unset($_SESSION['rem_passwordAvatar']);
                  }?>">
                  <label for="passwordAvatar"><h5 class="modcon2">Password</h5></label>
                </div></div>
                
                <div class="row"><div class="col s12 m10 push-m2" style="margin-bottom: 10px;">
                    <div class="g-recaptcha" data-sitekey="6Lcs3GIUAAAAAPOX9QzHOA_farHU1IKYvWrWpB-Z"></div>
            	</div></div>

                <div class="row"><div class="col s12">
                <button class="btn waves-effect waves-light nav-button" type="submit" name="action">Update<i class="material-icons right">send</i></button></div></div>
            </form>
            <?php
                if(isset($_SESSION['errorAvatar']))
                {
                	echo '<h5 class="errorColor">';
                    echo $_SESSION['errorAvatar'];
                    unset($_SESSION['errorAvatar']);
                    echo '</h5>';
                }
                else if(isset($_SESSION['successAvatar']))
                {
                	echo '<h5 class="successColor">';
                    echo $_SESSION['successAvatar'];
                    unset($_SESSION['successAvatar']);
                    echo '</h5>';
                }
            ?>
        </div>
        </div>
        
    </div>

<?php require_once("../../common/footer.php"); ?>