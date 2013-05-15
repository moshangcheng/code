module namespace shu = 'http://www.microstrategy.com/xquery/test/shu';

declare namespace op = "http://www.zorba-xquery.org/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

declare function shu:push($output as item(), $data as item()) as item()+
{
    $output, $data
};


declare function shu:test-xquery-script() as xs:integer
{
    variable $x := 1;
    variable $y := $x * 2;
    $y
};

declare function shu:test-fn-trace()
{
    variable $xml := <root><nodes><node>3</node></nodes></root>;
    fn:trace($xml, "this is xml trace: ")
    ;
};
