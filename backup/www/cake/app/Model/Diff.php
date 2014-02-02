<?php
class Diff extends AppModel {
    public $useTable = 'diff';
    public $hasOne = 'Queue';
}
?>
