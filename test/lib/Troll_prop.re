open Framework;
open QCheckRely;
open Generator.Fantasy;
open Lib.Troll;

let {describe} = extendDescribe(QCheckRely.Matchers.matchers);

describe("Troll Invariance", ({test}) => {
  test("Troll score should be 0 when all elves resurrected", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Troll score should be 0 when all elves resurrected",
      troll_arbitrary,
      troll =>
      all_elves_resurrected(troll) |> scoring == 0
    )
    |> expect.ext.qCheckTest;
    ();
  });
  test("Troll score should always be >= 0", ({expect}) => {
       QCheck.Test.make(
        ~count=1000,
        ~name="Troll value should always be positive or 0",
        troll_arbitrary,
        troll =>
        scoring(troll)>= 0
      )
      |> expect.ext.qCheckTest;
    ()
  });
});

describe("Troll Inverse", ({test}) => {
  test("oops_he_survived should always be inverse of i_got_one", ({expect}) => {
    QCheck.Test.make(
        ~count=1000,
        ~name="Troll inverse",
        troll_elf_arbitrary,
        ((troll,elf)) =>
        scoring(troll|>i_got_one(elf)|>oops_he_survived(elf))==scoring(troll)
      )
      |> expect.ext.qCheckTest;
    () 
  })
});

describe("Troll Analogy", ({test}) => {
  test("i_got_one and i_got should be consistent", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Troll inverse",
      troll_elf_int_arbitrary,
      ((troll,elf,x)) => {
        let tmp=ref(troll);
        for(y in 1 to x){
          tmp:=i_got_one(elf,tmp^)
        };
      
      scoring(tmp^)==scoring(i_got(x,elf,troll))
      }
    )
    |> expect.ext.qCheckTest;
  })
});

describe("Troll Idempotence", ({test}) => {
  test(
    "all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",
    ({expect}) => {
    QCheck.Test.make(
        ~count=1000,
        ~name="Troll inverse",
        troll_elf_int_arbitrary,
      ((troll,elf,x)) =>{
        let x=x+1;
        let tmp=ref(troll);
        for(y in 1 to x){
          tmp:=all_elves_of_a_kind_resurrected(elf,tmp^)
        };
      
        scoring(tmp^) == scoring(all_elves_of_a_kind_resurrected(elf,troll))
      }

      )
      |> expect.ext.qCheckTest;
    ()
  })
});