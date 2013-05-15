module namespace shu = 'http://www.microstrategy.com/xquery/test/shu';

declare namespace op = "http://www.zorba-xquery.org/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

declare function shu:push($ans as item(), $data as item()) as item()+
{
    return $ans
};