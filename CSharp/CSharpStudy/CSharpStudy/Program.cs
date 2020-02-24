using System;
using System.Threading.Tasks;

namespace CSharpStudy
{
    class Coffee
    {
        public Coffee() { }
    }

    class Egg
    {
    }

    class Bacon
    {
    }

    class Toast
    {
    }

    class Juice
    {

    }

    class Program
    {
        static async Task Main(string[] args)
        {
            Coffee cup = PourCoffee();
            Console.WriteLine("coffee is ready");

            Egg eggs = await FryEggs(2);
            Console.WriteLine("eggs is ready");

            Bacon bacon = await FryBacon(3);
            Console.WriteLine("bacon is ready");

            Toast toast = await ToastBread(2);
            ApplyButter(toast);
            ApplyJam(toast);
            Console.WriteLine("toast is ready");

            Juice oj = PourOrangeJuice();
            Console.WriteLine("oj is ready");

            Console.WriteLine("breakfast is ready");
        }

        private static Juice PourOrangeJuice()
        {
            return null;
        }

        private static void ApplyJam(Toast toast)
        {
            return;
        }

        private static void ApplyButter(Toast toast)
        {
            return;
        }

        private static Task<Toast> ToastBread(int num)
        {
            return null;
        }

        private static Task<Bacon> FryBacon(int num)
        {
            return null;
        }

        private static Task<Egg> FryEggs(int num)
        {
            return null;
        }

        private static Coffee PourCoffee()
        {
            return null;
        }
    }
}

// 혼자서 아침식사 준비하기 - 병렬로 수행 되지 않는 비동기 작업
// 요리에 익숙한 사람은 
// 커피를 올려놓고 준비되길 기다리면서
// 펜을 대우고 계란 후라이를 올리고
// 베이컨을 튀긴다
// 빵을 토스터기에 넣어놓고
// 토스트에 버터와 잼을 바르고
// 오렌지 주스 한잔 따름


// 병렬 알고리즘 은 여러 요리사 (스레드)가 필요하다
// 한사람은 계란만 후라이 하고
// 또 한사람은 베이컨만 굽는다
// 각 사람은 요리가 완성 되기전까지 독립적이다 (동기적으로 차단 됨)

// https://docs.microsoft.com/ko-kr/dotnet/csharp/programming-guide/concepts/async/