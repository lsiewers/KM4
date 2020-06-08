<br>

<p>
    You can change the strictness of your perfect rhythm. <br>
    <small>Your bedtimes are depended on your chronotype and your recorded bedtimes</small>
    <small>If the strictness is high, your recommended bedtime will be more influenced by your chronotype</small><br>
    <small>If the strictness is low, your recommended bedtime will be more influenced by your average bedtime</small>
</p>

<form action="devicePreferences_update.php">
    <label for="strictness">strictness</label><br>
    <input name="strictness" type="range" value="<?= $deviceRow['strictness'] * 100 ?>" min="0" max="100"><br>
    <input type="submit" value="update">
</form>

<p>Your upcoming bedtimes:</p>
<pre>In bed time (sunset): <?= $deviceRow["sunsetTime"] ?></pre>
<pre>Awake time (sunrise): <?= $deviceRow["sunriseTime"] ?></pre>
